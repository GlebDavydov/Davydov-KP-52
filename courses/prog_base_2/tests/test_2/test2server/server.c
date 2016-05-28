#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>

#include "server.h"

typedef enum resp_s{HTML, XML}resp_t;

struct keyvalue_s{
    char key[256];
    char value[256];
};

struct http_request_s{
    char method[8];
    char uri[256];
    keyvalue_t * form;
    int formLength;
};

http_request_t
http_request_parse(const char * const request) {
    http_request_t req;
    req.form = NULL;
    req.formLength = 0;
    // get method
    ptrdiff_t methodLen = strstr(request, " ") - request;  // find first whitespace
    memcpy(req.method, request, methodLen);
    req.method[methodLen] = '\0';
    // get uri
    const char * uriStartPtr = request + strlen(req.method) + 1;
    const char * uriEndPtr = strstr(uriStartPtr, " ");  // find second whitespace
    ptrdiff_t uriLen = uriEndPtr - uriStartPtr;
    memcpy(req.uri, uriStartPtr, uriLen);
    req.uri[uriLen] = '\0';
    // parse form data
    const char * bodyStartPtr = strstr(request, "\r\n\r\n") + strlen("\r\n\r\n");
    const char * cur = bodyStartPtr;
    const char * pairEndPtr = cur;
    const char * eqPtr = cur;
    while (strlen(cur) > 0) {
        pairEndPtr = strchr(cur, '&');
        if (NULL == pairEndPtr) {
            pairEndPtr = cur + strlen(cur);
        }
        keyvalue_t kv;
        // get key
        eqPtr = strchr(cur, '=');
        ptrdiff_t keyLen = eqPtr - cur;
        memcpy(kv.key, cur, keyLen);
        kv.key[keyLen] = '\0';
        // get value
        eqPtr++;
        ptrdiff_t valueLen = pairEndPtr - eqPtr;
        memcpy(kv.value, eqPtr, valueLen);
        kv.value[valueLen] = '\0';
        // insert key-value pair into request form list
        req.formLength += 1;
        req.form = realloc(req.form, sizeof(keyvalue_t) * req.formLength);
        req.form[req.formLength - 1] = kv;
        cur = pairEndPtr + ((strlen(pairEndPtr) > 0) ? 1 : 0);
    }
    return req;
}

const char *
http_request_getArg(http_request_t * self, const char * key) {
    for (int i = 0; i < self->formLength; i++) {
        if (strcmp(self->form[i].key, key) == 0) {
            return self->form[i].value;
        }
    }
    return NULL;
}

const char * keyvalue_toString(keyvalue_t * self) {
    char * str = malloc(sizeof(char) * (strlen(self->key) + strlen(self->value) + 2));
    sprintf(str, "%s=%s\0", self->key, self->value);
    return str;
}

void http_request_startServer(list_t *list){
    lib_init();
    socket_t * serverSocket = socket_new();
    socket_bind(serverSocket, 5000);
    socket_listen(serverSocket);
    while(1){
        puts("Waiting for connections");
        socket_t * clientSocket = socket_accept(serverSocket);
        puts("New client");
        char buff[BUFFER_LENGTH];
        int readLength = socket_read(clientSocket, buff, BUFFER_LENGTH);
        if(readLength == 0){
            socket_close(clientSocket);
            socket_free(clientSocket);
            puts("Skipping empty request");
            continue;
        }

        printf("Got Request:\n---------------\n%s\n----------------\n", buff);

        http_request_t req = http_request_parse(buff);

        printf("Method: %s\nURI: %s\n", req.method, req.uri);
        puts("Data:");
        for(int i = 0; i < req.formLength; i++){
            char * kvStr = keyvalue_toString(&req.form[i]);
            printf("\t%s\n", kvStr);
            free(kvStr);
        }
        http_request_chooseMethod(req, clientSocket, list);
        socket_close(clientSocket);
        socket_free(clientSocket);
    }
    socket_close(serverSocket);
    socket_free(serverSocket);
    lib_free();
}

char *resp_form(resp_t type, char *usermsg, int code, char *buffer){
    char msg[MSG_LENGTH];
    if(type == XML){
        switch(code){
        case 200:
            {
                sprintf(buffer,
                        "HTTP/1.1 200 OK\n"
                        "Content-length: %zu\n"
                        "Content-type: application/xml\n"
                        "\n"
                        "%s\0", strlen(usermsg), usermsg);
                break;
            }
        case 403:
            {
                sprintf(msg, "<message>\n"
                        "\t<status>ERROR</status>\n"
                        "<text>Error 403: forbidden</text>"
                        "</message>");
                sprintf(buffer,
                        "HTTP/1.1 403 Error\n"
                        "Content-length: %zu\n"
                        "Content-type: application/xml\n"
                        "\n"
                        "%s\0", strlen(msg), msg);
                break;
            }
        case 404:
            {
                sprintf(msg, "<message>\n"
                        "\t<status>ERROR</status>\n"
                        "<text>Error 404: not found</text>"
                        "</message>");
                sprintf(buffer,
                        "HTTP/1.1 403 Error\n"
                        "Content-length: %zu\n"
                        "Content-type: application/xml\n"
                        "\n"
                        "%s\0", strlen(msg), msg);
                break;
            }
        default:
            {
                sprintf(msg, "<message>\n"
                        "\t<status>ERROR</status>\n"
                        "<text>Error 502: bad gateway</text>"
                        "</message>");
                sprintf(buffer,
                        "HTTP/1.1 502 Error\n"
                        "Content-length: %zu\n"
                        "Content-type: application/xml\n"
                        "\n"
                        "%s\0", strlen(msg), msg);
                break;
            }
        }
    } else if (type == HTML){
        switch(code){
            case 200:
                sprintf(msg, "<!DOCTYPE html>"
                        "<html>"
                        "<head>"
                            "<title></title>" //!REMEMBER TO SET YOUR TITLE!
                        "</title>"
                        "</head>"
                        "<body>"
                        "%s"
                        "</body>"
                        "</html>");
                sprintf(buffer,
                        "HTTP/1.1 200 OK\n"
                        "Content-length: %zu\n"
                        "Content-type: text/html\n"
                        "\n"
                        "%s\0", strlen(msg), msg);
                break;
            case 403:
                sprintf(msg, "<!DOCTYPE html>"
                        "<html>"
                        "<head>"
                            "<title>403 forbidden</title>" //!REMEMBER TO SET YOUR TITLE!
                        "</title>"
                        "</head>"
                        "<body>"
                        "<h3>Error 403: forbidden</h3>"
                        "</body>"
                        "</html>");
                sprintf(buffer,
                        "HTTP/1.1 403 Error\n"
                        "Content-length: %zu\n"
                        "Content-type: text/html\n"
                        "\n"
                        "%s\0", strlen(msg), msg);
                break;
            case 404:
                sprintf(msg, "<!DOCTYPE html>"
                        "<html>"
                        "<head>"
                            "<title>404 not found</title>" //!REMEMBER TO SET YOUR TITLE!
                        "</title>"
                        "</head>"
                        "<body>"
                        "<h3>Error 404: not found</h3>"
                        "</body>"
                        "</html>");
                sprintf(buffer,
                        "HTTP/1.1 404 Error\n"
                        "Content-length: %zu\n"
                        "Content-type: text/html\n"
                        "\n"
                        "%s\0", strlen(msg), msg);
                break;
            default:
                sprintf(msg, "<!DOCTYPE html>"
                        "<html>"
                        "<head>"
                            "<title>502 bad gateway</title>" //!REMEMBER TO SET YOUR TITLE!
                        "</title>"
                        "</head>"
                        "<body>"
                        "<h3>Error 502: bad gateway</h3>"
                        "</body>"
                        "</html>");
                sprintf(buffer,
                        "HTTP/1.1 502 Error\n"
                        "Content-length: %zu\n"
                        "Content-type: text/html\n"
                        "\n"
                        "%s\0", strlen(msg), msg);
                break;
        }
    }
    return buffer;
}

void http_request_chooseMethod(http_request_t req, socket_t * clientSocket, list_t *list){
    if(!strcmp(req.uri, "/")){
        char smallMSG[100];
        sprintf(smallMSG, "<h1>HELLO!!!</h1>");
        char result_msg[MSG_LENGTH];
        resp_form(HTML, smallMSG, 200, result_msg);
        socket_write_string(clientSocket, result_msg);
    }
    else if(!strcmp(req.uri, "/info")){
        char result_msg[MSG_LENGTH];
        resp_form(XML, me_to_message(), 200, result_msg);
        socket_write_string(clientSocket, result_msg);
    }else{
        char result_msg[MSG_LENGTH];
        resp_form(XML, NULL, 404, result_msg);
        socket_write_string(clientSocket, result_msg);
        return;
    }
}

