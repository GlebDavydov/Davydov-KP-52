#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "server.h"
#include "FS_module.h"

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
    sqlite3 *db;
    int rc = 0;
    rc = sqlite3_open("teachers.db", &db);
    if(SQLITE_OK != rc){
        return;
    }
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
        http_request_chooseMethod(req, clientSocket, list, db);
        socket_close(clientSocket);
        socket_free(clientSocket);
    }
    socket_close(serverSocket);
    socket_free(serverSocket);
    sqlite3_close(db);
    free(db);
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
                            "<title>Davydov KP-52 Var24</title>"
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
                            "<title>403 forbidden</title>"
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
                            "<title>404 not found</title>"
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
                            "<title>502 bad gateway</title>"
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

void http_request_chooseMethod(http_request_t req, socket_t * clientSocket, list_t *list, sqlite3 *db){
    if(!strcmp(req.method, "GET")){
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
    }else if(!strcmp(req.uri, "/external")){
        static const char * requestFormat =
        "%s %s HTTP/1.1\r\n"
        "Content-Type: text\r\n"
        "Content-Length: %zu\r\n\r\n"
        "%s";
        socket_t* serverSock = socket_new ();
        socket_connect(serverSock, "216.58.209.49", 80);
        char uri [256];
        strcpy (uri, "http://pb-homework.appspot.com/test/var/32?format=xml");
        char req [1024];
        sprintf (req, requestFormat, "GET", uri, NULL, NULL, NULL);
        socket_write(serverSock, req, strlen (req));
        char responce [1024];
        socket_read (serverSock, responce, 1024);
        int contentLength = 0;
        sscanf (strstr(responce, "Content-Length: ") + strlen ("Content-Length: "), "%d", &contentLength);
        char* data = strstr (responce, "\r\n\r\n") + 4;
        socket_free(serverSock);
        data = parse_response(data);
        char result_msg[MSG_LENGTH];
        resp_form(XML, data, 200, result_msg);
        socket_write_string(clientSocket, result_msg);
    }else if(!strcmp(req.uri, "/database")){
        char result_msg[MSG_LENGTH];
        read_all_teachers(db, list);
        char SomeMsg[MSG_LENGTH];
        strcpy(SomeMsg, all_teachers_to_message(list));
        resp_form(XML, SomeMsg, 200, result_msg);
        socket_write_string(clientSocket, result_msg);;
    } else if(!strcmp(req.uri, "/file-remove")){
        char formMessage[MSG_LENGTH];
        sprintf(formMessage, "<!DOCTYPE html>"
"<html>"
    "<head>"
        "<title>KPI FPM TDB</title>"
    "</head>"
    "<body>"
        "<h3>New person</h3>"
        "<form action=\"/filesystem/\" method=\"POST\">"
  "Enter file name:<br>"
  "<input type=\"text\" name=\"filename\"><br>"
  "<input type=\"submit\" value=\"Submit\">"
"</form>"
    "</body>"
"</html>");
        socket_write_string(clientSocket, formMessage);
    }else if(!strcmp(req.uri, "/filesystem/")){
        char result_msg[MSG_LENGTH];
        resp_form(XML, NULL, 403, result_msg);
        socket_write_string(clientSocket, result_msg);
        return;
    }else {
        char result_msg[MSG_LENGTH];
        resp_form(XML, NULL, 404, result_msg);
        socket_write_string(clientSocket, result_msg);
        return;
    }}
    else if(!strcmp(req.method, "POST")){
    if(!strcmp(req.uri, "/filesystem/")){
        char result_msg[MSG_LENGTH];
        char *filename = http_request_getArg(&req, "filename");
        if(!filename){
            resp_form(XML, NULL, 404, result_msg);
            socket_write_string(clientSocket, result_msg);
            return;
        }
        if(!file_exists(filename)){
            resp_form(XML, NULL, 404, result_msg);
            socket_write_string(clientSocket, result_msg);
            return;
        }
        if(!strcmp(filename, "teachers.db")){
            char result_msg[MSG_LENGTH];
        resp_form(XML, NULL, 403, result_msg);
        socket_write_string(clientSocket, result_msg);
        return;
        }
        file_remove(filename);
        char *msg = "<message><status>OK</status><text>File deleion done</text></message>";
        resp_form(XML, msg, 200, result_msg);
        socket_write_string(clientSocket, result_msg);

    }}else{
        char result_msg[MSG_LENGTH];
        resp_form(XML, NULL, 403, result_msg);
        socket_write_string(clientSocket, result_msg);
        return;
    }
}

