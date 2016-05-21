#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>

#include "server.h"

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

int checkDate(char *date){
    if(strlen(date) != 10){
        return 0;
    }
    for(int i = 0; i < 10; i++){
        if(i == 2 || i == 5){
            if(date[i] != '.'){
                return 0;
            }
        } else {
            if(!isdigit(date[i]))
                return 0;
        }
    }
    return 1;
}

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

void http_request_chooseMethod(http_request_t req, socket_t * clientSocket, list_t *list){
    if(!strcmp(req.uri, "/"))
        {
        char msg[MSG_LENGTH];
        sprintf(msg,
                    "<!DOCTYPE html>"
"<html>"
    "<head>"
        "<title>KPI FPM TDB</title>"
    "</head>"
    "<body>"

            "<h1>KPI FPM TEACHERS DATABASE</h1>"
            "<p>Welcome user! </p>"
            "<a href=\"/teachers\">All teachers</a>"

    "</body>"
"</html>"
                    /*"<message>\n"
                    "\t<status>ok</status>\n"
                    "\t<text>HELLO, USER!</text>\n"
                    "</message>\n"*/);
        socket_write_string(clientSocket, msg);
        }
    /*else if (!strcmp(req.uri, "/teachers"))
        {
        char msg[MSG_LENGTH];
        sprintf(msg, "<message>\n"
                    "\t<status>error</status>\n"
                    "\t<text>Not Found</text>\n"
                    "</message>\n");
        socket_write_string(clientSocket, msg);
        }*/
    else
        if (strcmp(req.uri, "/teachers") == 0)
        {
            if(strcmp(req.method, "GET") == 0){
                char tempBuff[MSG_LENGTH];
                sprintf(tempBuff, "<table>"
                        "<caption>OUR BEST</caption>"
        "<tr>"
            "<th>Id</th>"
            "<th>First Name</th>"
            "<th>Last Name</th>"
	"</tr>");
                for(int i = 0; i < list_count(list); i++){
                    sprintf(tempBuff, "%s"
    "<tr>"
		"<th><a href=\"/teachers/%d\">%d</a></th>"
		"<th>%s</th>"
		"<th>%s</th>"
	"</tr>", tempBuff, list_id(list, i), list_id(list, i), list_get(list, i)->name, list_get(list, i)->surname);
                }
                    char result[10000];
                    sprintf(result,
                        "<!DOCTYPE html>"
"<html>"
    "<head>"
        "<title>KPI FPM TDB</title>"
    "</head>"
    "<body>"

            "<h3>ALL TEACHERS</h3>"
            "%s"
            "</table>"
            "<a href=\"/teachers/new\"></a>"


    "</body>"
"</html>"
                        /*"HTTP/1.1 200 OK\n"
                        "Content-length: %zu\n"
                        "Content-type: application/xml\n"
                        "\n"
                        "%s\0",
                        strlen(all_teachers_to_message(list)), all_teachers_to_message(list)*/, tempBuff);
                    socket_write_string(clientSocket, result);
                }
            else {
                char result_msg[MSG_LENGTH];
                sprintf(result_msg,
                        "<!DOCTYPE html>"
"<html>"
    "<head>"
        "<title>KPI FPM TDB</title>"
    "</head>"
    "<body>"
        "<p>Error: not allowed</p>"
    "</body>"
"</html>"
                        /*"<message>\n"
                        "\t<status>error</status>\n"
                        "\t<text>NOT ALLOWED</text>\n"
                        "</message>\n"*/);
                socket_write_string(clientSocket, result_msg);
            }
        }
    else if (strcmp(req.uri, "/teachers") > 0)
        {if(strcmp(req.method, "POST") == 0)
                {
                    char result[MSG_LENGTH];
                    const char * fName = http_request_getArg(&req, "firstName");
                    const char * lName = http_request_getArg(&req, "lastName");
                    const char * pensDate = http_request_getArg(&req, "pensionDate");
                    double rating = atof(http_request_getArg(&req, "rating"));
                    int  hours = atoi(http_request_getArg(&req, "hours"));
                    const char * cName = http_request_getArg(&req, "cathedra");
                    const char * sName = http_request_getArg(&req, "speciality");
                    const char * g1Name = http_request_getArg(&req, "group1");
                    const char * g2Name = http_request_getArg(&req, "group2");
                    if(!fName || !lName || !pensDate ||
                       !cName || !sName || !g1Name || !g2Name){
                        sprintf(result,"<!DOCTYPE html>"
"<html>"
    "<head>"
        "<title>KPI FPM TDB</title>"
    "</head>"
    "<body>"
        "<p>Error: empty argument</p>"
    "</body>"
"</html>"
                            /*"<message>\n"
                            "\t<status>error</status>\n"
                            "\t<text>Empty argument(s)</text>\n"
                            "</message>\n"*/);
                            socket_write_string(clientSocket, result);
                            return 1;
                       }
                    else if(strlen(fName) == 0 || strlen(fName) > WORD_LENGTH || strlen(lName) == 0 || strlen(lName) > WORD_LENGTH){
                            sprintf(result,"<!DOCTYPE html>"
"<html>"
    "<head>"
        "<title>KPI FPM TDB</title>"
    "</head>"
    "<body>"
        "<p>Error: not allowed</p>"
    "</body>"
"</html>"
                            /*"<message>\n"
                            "\t<status>error</status>\n"
                            "\t<text>Invalid name</text>\n"
                            "</message>\n"*/);
                            socket_write_string(clientSocket, result);
                            return 1;
                    } else if(!checkDate(pensDate)){
                        sprintf(result,"<!DOCTYPE html>"
"<html>"
    "<head>"
        "<title>KPI FPM TDB</title>"
    "</head>"
    "<body>"
        "<p>Error: not allowed</p>"
    "</body>"
"</html>"
                            /*"<message>\n"
                            "\t<status>error</status>\n"
                            "\t<text>Invalid pension date</text>\n"
                            "</message>\n"*/);
                            socket_write_string(clientSocket, result);
                            return 1;
                    } else if(strlen(cName) == 0 || strlen(cName) > WORD_LENGTH){
                        sprintf(result,"<!DOCTYPE html>"
"<html>"
    "<head>"
        "<title>KPI FPM TDB</title>"
    "</head>"
    "<body>"
        "<p>Error: not allowed</p>"
    "</body>"
"</html>"/*
                            "<message>\n"
                            "\t<status>error</status>\n"
                            "\t<text>Invalid cathedra</text>\n"
                            "</message>\"n*/);
                            socket_write_string(clientSocket, result);
                            return 1;
                    } else if(rating < 0 || rating > 10.0){
                        sprintf(result,"<!DOCTYPE html>"
"<html>"
    "<head>"
        "<title>KPI FPM TDB</title>"
    "</head>"
    "<body>"
        "<p>Error: not allowed</p>"
    "</body>"
"</html>"/*
                            "<message>\n"
                            "\t<status>error</status>\n"
                            "\t<text>Invalid score</text>\n"
                            "</message>\n"*/);
                            socket_write_string(clientSocket, result);
                            return 1;
                    } else if(strlen(sName) == 0 || strlen(sName) > WORD_LENGTH){
                        sprintf(result,"<!DOCTYPE html>"
"<html>"
    "<head>"
        "<title>KPI FPM TDB</title>"
    "</head>"
    "<body>"
        "<p>Error: not allowed</p>"
    "</body>"
"</html>"/*
                            "<message>\n"
                            "\t<status>error</status>\n"
                            "\t<text>Invalid speciality</text>\n"
                            "</message>\n"*/);
                            socket_write_string(clientSocket, result);
                            return 1;
                    } else if(strlen(g1Name) == 0 || strlen(g1Name) > WORD_LENGTH || strlen(g2Name) == 0 || strlen(g2Name) > WORD_LENGTH){
                        sprintf(result,"<!DOCTYPE html>"
"<html>"
    "<head>"
        "<title>KPI FPM TDB</title>"
    "</head>"
    "<body>"
        "<p>Error: not allowed</p>"
    "</body>"
"</html>"
                            /*"<message>\n"
                            "\t<status>error</status>\n"
                            "\t<text>Invalid group</text>\n"
                            "</message>\n"*/);
                            socket_write_string(clientSocket, result);
                            return 1;
                     }else {
                    int this = list_add(list, new_teacher());
                    teacher_update(list_get(list, list_find_id(list, this)), fName, lName, pensDate, hours, rating, cName, sName, g1Name, g2Name);
                      /*printf("New:\n"
                           "<teacher>\n"
                            "\t<id>%i</id>\n"
                            "\t<firstName>%s</firstName>\n"
                            "\t<lastName>%s</lastName>\n"
                            "\t<pensionDate>%s</penstionDate>\n"
                            "\t<hours>%d</hours>\n"
                            "\t<rating>%.2f</rating>\n"
                            "\t<cathedra nameCathedra=\"%s\">\n"
                            "\t\t<speciality>%s<speciality>\n"
                            "\t\t<group1>%s</group1>\n"
                            "\t\t<group2>%s</group2>\n"
                            "\t</cathedra>\n"
                            "</teacher>\n\n",
                            this, fName, lName, pensDate, hours, rating, cName, sName, g1Name, g2Name);
                        char res[MSG_LENGTH];
                        sprintf(res, "<teacher>\n"
                                "\t<id>%i</id>\n"
                                "\t<firstName>%s</firstName>\n"
                                "\t<lastName>%s</lastName>\n"
                                "\t<pensionDate>%s</penstionDate>\n"
                                "\t<hours>%d</hours>\n"
                                "\t<rating>%.2f</rating>\n"
                                "\t<cathedra nameCathedra=\"%s\">\n"
                                "\t\t<speciality>%s<speciality>\n"
                                "\t\t<group1>%s</group1>\n"
                                "\t\t<group2>%s</group2>\n"
                                "\t</cathedra>\n"
                                "</teacher>\n\n",
                               this, fName, lName, pensDate, hours, rating, cName, sName, g1Name, g2Name);*/
                        sprintf(result,"<!DOCTYPE html>"
"<html>"
    "<head>"
        "<title>KPI FPM TDB</title>"
    "</head>"
    "<body>"
        "<p>ID %d successfully added</p>"
    "</body>"
"</html>"

                                , /*
                                "HTTP/1.1 200 OK\n"
                                "Content-length: %zu\n"
                                "Content-type: application/xml\n"
                                "\n"
                                "%s\0",
                                strlen(res), res*/this);
                        socket_write_string(clientSocket, result);
                        return 1;
                        }
                    }
        else if(!strcmp(req.uri, "/teachers/new")){
            if(!strcmp(req.method, "GET")){
                    char result_msg[MSG_LENGTH];
                    sprintf(result_msg, "<!DOCTYPE html>"
"<html>"
    "<head>"
        "<title>KPI FPM TDB</title>"
    "</head>"
    "<body>"
        "<h3>New person</h3>"
        "<form action=\"/teachers/\" method=\"POST\">"
  "First name:<br>"
  "<input type=\"text\" name=\"firstName\"><br>"
  "Last name:<br>"
  "<input type=\"text\" name=\"lastName\">"
  "<br>"
  "Pension date:<br>"
  "<input type=\"text\" name=\"pensionDate\">"
  "<br>"
  "Hours:<br>"
  "<input type=\"text\" name=\"hours\">"
  "<br>"
  "Rating:<br>"
  "<input type=\"text\" name=\"rating\">"
  "<br>"
  "Cathedra:<br>"
  "<input type=\"text\" name=\"cathedra\">"
  "<br>"
  "Speciality:<br>"
  "<input type=\"text\" name=\"speciality\">"
  "<br>"
  "Group 1:<br>"
  "<input type=\"text\" name=\"group1\">"
  "<br>"
  "Group 2:<br>"
  "<input type=\"text\" name=\"group2\">"
  "<br>"
  "<input type=\"submit\" value=\"Submit\">"
"</form>"

    "</body>"
"</html>");
                    socket_write_string(clientSocket, result_msg);
                }else {
                    char result_msg[MSG_LENGTH];
                    sprintf(result_msg,
                            "<!DOCTYPE html>"
"<html>"
    "<head>"
        "<title>KPI FPM TDB</title>"
    "</head>"
    "<body>"
        "<p>Error: not allowed</p>"
    "</body>"
"</html>"
                            /*"<message>\n"
                            "\t<status>error</status>\n"
                            "\t<text>NOT ALLOWED</text>\n"
                            "</message>\n"*/);
                    socket_write_string(clientSocket, result_msg);
                    return 1;
                }
        }else{
        int id = atoi(strtok(req.uri, "/teachers"));
        if(list_find_id(list, id) != -1)
            {
            if(strcmp(req.method, "GET") == 0)
                {
                if(teacher_to_message(list_get(list, list_find_id(list, id)), id) != NULL)
                    {
                        char result[BUFFER_LENGTH];
                        teacher_t *t = list_get(list, list_find_id(list, id));
                        sprintf(result, "<!DOCTYPE html>"
"<html>"
    "<head>"
        "<title>KPI FPM TDB</title>"
    "</head>"
    "<body>"
        "<h3>%s %s</h3>"
        "<table>"
            "<tr>"
                "<th>ID:</th>"
                "<th>hours:</th>"
                "<th>rating:</th>"
                "<th>cathedra:</th>"
                "<th>speciality</th>"
                "<th>group 1:</th>"
                "<th>group 2:</th>"
                "<th>pension date:</th>"
            "</tr>"
            "<tr>"
                "<th>%d</th>"
                "<th>%d</th>"
                "<th>%.2f</th>"
                "<th>%s</th>"
                "<th>%s</th>"
                "<th>%s</th>"
                "<th>%s</th>"
                "<th>%s</th>"
            "</tr>"
        "</table>"
        "<a href=\"#\" onclick=\"doDelete()\">Delete</a>"
        "<script>"
            "function doDelete() {"
                "var xhttp = new XMLHttpRequest();"
                "xhttp.open(\"DELETE\", \"http://127.0.0.1:5000/teachers/%d\", true);"
                "xhttp.send();"
            "}"
        "</script>"
    "</body>"
"</html>"
                            /*"HTTP/1.1 200 OK\n"
                            "Content-length: %zu\n"
                            "Content-type: application/xml\n"
                            "\n"
                            "%s\0",
                            strlen(teacher_to_message(t, id)), teacher_to_message(t, id)*/
                            , t->name, t->surname,
                             id, t->hours, t->rating, t->cathedra->name, t->cathedra->speciality, t->cathedra->groups[0],
                             t->cathedra->groups[1], t->date, id);
                        socket_write_string(clientSocket, result);
                        return 1;
                    }
                }
                else if(strcmp(req.method, "DELETE") == 0)
                {
                    free_teacher(list_remove(list, list_find_id(list, id)));
                    char result_msg[MSG_LENGTH];
                    sprintf(result_msg,
                            "<!DOCTYPE html>"
"<html>"
    "<head>"
        "<title>KPI FPM TDB</title>"
    "</head>"
    "<body>"
        "<p>%d successfully deleted</p>"
    "</body>"
"</html>",/*
                            "<message>\n"
                            "\t<status>ok</status>\n"
                            "\t<text>Teacher (id%i) has been deleted</text>\n"
                            "</message>\n",*/ id);
                    socket_write_string(clientSocket, result_msg);
                    return 1;
                }else {
                    char result_msg[MSG_LENGTH];
                    sprintf(result_msg,
                            "<!DOCTYPE html>"
"<html>"
    "<head>"
        "<title>KPI FPM TDB</title>"
    "</head>"
    "<body>"
        "<p>Error: not allowed</p>"
    "</body>"
"</html>"
                            /*"<message>\n"
                            "\t<status>error</status>\n"
                            "\t<text>NOT ALLOWED</text>\n"
                            "</message>\n"*/);
                    socket_write_string(clientSocket, result_msg);
                    return 1;
                }
            }
            else {
                char result_msg[MSG_LENGTH];
                sprintf(result_msg,
                        "<!DOCTYPE html>"
"<html>"
    "<head>"
        "<title>KPI FPM TDB</title>"
    "</head>"
    "<body>"
        "<p>Error: %d not found</p>"
    "</body>"
"</html>"
                        /*
                        "<message>\n"
                        "\t<status>error</status>\n"
                        "\t<text>Teacher (id%i) not found</text>\n"
                        "</message>\n",*/, id);
                socket_write_string(clientSocket, result_msg);
                return 1;
            }

            }
        }
    else
    {
            char result_msg[MSG_LENGTH];
            sprintf(result_msg,
                    "<!DOCTYPE html>"
"<html>"
    "<head>"
        "<title>KPI FPM TDB</title>"
    "</head>"
    "<body>"
        "<p>Error: not found</p>"
    "</body>"
"</html>"
                            /*"<message>\n"
                            "\t<status>error</status>\n"
                            "\t<text>Not Found</text>\n"
                            "</message>\n"*/);
            socket_write_string(clientSocket, result_msg);
            return 1;
    }
}

