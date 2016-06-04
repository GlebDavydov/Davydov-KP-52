#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "server.h"

typedef enum resp_s {HTML, XML} resp_t;

struct keyvalue_s
{
    char key[256];
    char value[256];
};

struct http_request_s
{
    char method[8];
    char uri[256];
    keyvalue_t * form;
    int formLength;
};

int date_check(char *date);

http_request_t
http_request_parse(const char * const request)
{
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
    while (strlen(cur) > 0)
    {
        pairEndPtr = strchr(cur, '&');
        if (NULL == pairEndPtr)
        {
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
http_request_getArg(http_request_t * self, const char * key)
{
    for (int i = 0; i < self->formLength; i++)
    {
        if (strcmp(self->form[i].key, key) == 0)
        {
            return self->form[i].value;
        }
    }
    return NULL;
}

const char * keyvalue_toString(keyvalue_t * self)
{
    char * str = malloc(sizeof(char) * (strlen(self->key) + strlen(self->value) + 2));
    sprintf(str, "%s=%s\0", self->key, self->value);
    return str;
}

void http_request_startServer(list_t *list)
{
    lib_init();
    sqlite3 *db;
    int rc = 0;
    rc = sqlite3_open("teachers.db", &db);
    if(SQLITE_OK != rc)
    {
        return;
    }
    socket_t * serverSocket = socket_new();
    socket_bind(serverSocket, 5000);
    socket_listen(serverSocket);
    while(1)
    {
        puts("Waiting for connections");
        socket_t * clientSocket = socket_accept(serverSocket);
        puts("New client");
        char buff[BUFFER_LENGTH];
        int readLength = socket_read(clientSocket, buff, BUFFER_LENGTH);
        if(readLength == 0)
        {
            socket_close(clientSocket);
            socket_free(clientSocket);
            puts("Skipping empty request");
            continue;
        }

        printf("Got Request:\n---------------\n%s\n----------------\n", buff);

        http_request_t req = http_request_parse(buff);

        printf("Method: %s\nURI: %s\n", req.method, req.uri);
        puts("Data:");
        for(int i = 0; i < req.formLength; i++)
        {
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

char *resp_form(resp_t type, char *usermsg, int code, char *buffer)
{
    char msg[MSG_LENGTH];
    if(type == XML)
    {
        switch(code)
        {
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
    }
    else if (type == HTML)
    {
        switch(code)
        {
        case 200:
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

void http_request_chooseMethod(http_request_t req, socket_t * clientSocket, list_t *list, sqlite3 *db)
{
    if(!strcmp(req.method, "GET"))
        {
            if(!strcmp(req.uri, "/"))
            {
                char smallMSG[10000];
                sprintf(smallMSG, "<!DOCTYPE html>"
                        "<html>"
                        "<head>"
                        "<title>KPI FPM TDB</title>"
                        "</head>"
                        "<body>"

                        "<h1>KPI FPM TEACHERS DATABASE</h1>"
                        "<p>Welcome user! </p>"
                        "<a href=\"/teachers\">All teachers</a>"

                        "</body>"
                        "</html>");
                //char result_msg[MSG_LENGTH];
                //resp_form(HTML, smallMSG, 200, result_msg);
                socket_write_string(clientSocket, smallMSG);
            }
            else if(!strcmp(req.uri, "/teachers"))
            {
                char result_msg[MSG_LENGTH];
                int err = 0;
                int *s = &err;
                read_all_teachers(db, list, s);
                if(err)
                    return;
                //char SomeMsg[MSG_LENGTH];
                all_teachers_to_html(list, result_msg);
                //all_teachers_to_message(list, SomeMsg);
                //resp_form(XML, SomeMsg, 200, result_msg);
                socket_write_string(clientSocket, result_msg);;
            }
            else if(!strcmp(req.uri, "/teachers/new"))
            {
                char result_msg[MSG_LENGTH];
                sprintf(result_msg, "<!DOCTYPE html>"
                        "<html>"
                        "<head>"
                        "<title>KPI FPM TDB</title>"
                        "</head>"
                        "<body>"
                        "<h3>New person</h3>"
                        "<form action=\"/teachers/\" method=\"POST\">"
                        "Passport:<br>"
                        "<input type=\"text\" name=\"passport\"><br>"
                        "First name:<br>"
                        "<input type=\"text\" name=\"fname\"><br>"
                        "Last name:<br>"
                        "<input type=\"text\" name=\"lname\">"
                        "<br>"
                        "Birthdate:<br>"
                        "<input type=\"text\" name=\"birthdate\">"
                        "<br>"
                        "Experience:<br>"
                        "<input type=\"text\" name=\"exp\">"
                        "<br>"
                        "Salary:<br>"
                        "<input type=\"text\" name=\"salary\">"
                        "<br>"
                        "Group:<br>"
                        "<input type=\"text\" name=\"group\">"
                        "<br>"
                        "<input type=\"submit\" value=\"Submit\">"
                        "</form>"

                        "<br>"
                        "<a href=\"/\">Home</a>"

                        "</body>"
                        "</html>");
                socket_write_string(clientSocket, result_msg);
            }
            else if(strcmp(req.uri, "/teachers")>0)
            {
                char result_msg[MSG_LENGTH];
                int err = 0;
                int *s = &err;
                read_all_teachers(db, list, s);
                if(err)
                    return;
                int pass = atoi(strtok(req.uri, "/teachers/"));
                teacher_t *t1 = new_teacher();
                if(list_contains_passport(list, pass) == -1)
                {
                    resp_form(XML, NULL, 404, result_msg);
                    socket_write_string(clientSocket, result_msg);
                    return;
                }
                read_teacher(db, pass, t1, s);
                char user_msg[MSG_LENGTH];
                //teacher_to_message(t1, pass, user_msg);
                teacher_to_html(t1, user_msg);
                //resp_form(XML, user_msg, 200, result_msg);
                free_teacher(t1);
                socket_write_string(clientSocket, user_msg);
            } else if(strcmp(req.uri, "/api/teachers") > 0)
            {
                char result_msg[MSG_LENGTH];
                int err = 0;
                int *s = &err;
                // Get request text.
        char requestToParse[1000] = "\0";
        sscanf(req.uri, "/api/teachers?%s", requestToParse);
        // Get request values.
        int arg1 = 0;
        double arg2 = 0;
        char fS[10] = "\0", sS[10] = "\0", yearsValStr[10] = "\0";
        char firstSign = 'a', secondSign = 'a';
        int checkCode = sscanf(requestToParse, "salary%3s%d&exp%3s%3s", fS, &arg1, sS, yearsValStr);
        arg2 = atof(yearsValStr);
        int state = 1;
        if (checkCode == 4)
        {
            if (!strcmp(fS, "%3C"))
            {
                state *=5;
            }
            else if (!strcmp(fS, "%3E"))
            {
                state *= 3;
            }
            if (!strcmp(sS, "%3C"))
            {
                state  *= 11;
            }
            else if (!strcmp(sS, "%3E"))
            {
                state *= 7;
            }
        }
        else{
            char result_msg[MSG_LENGTH];
                resp_form(XML, NULL, 403, result_msg);
                socket_write_string(clientSocket, result_msg);
                return;
        }
            char user_msg[MSG_LENGTH];
            int c = list_count(list);
            for(int i = 0; i < c; i++){
                list_remove(list, 0);
            }
            select_teachers(db, list, arg1, arg2, s, state);
            all_teachers_to_message(list, user_msg);
            resp_form(XML, user_msg, 200, result_msg);
            socket_write_string(clientSocket, result_msg);
            return;
    }else if(!strcmp(req.uri, "/api/teachers"))
            {
                char result_msg[MSG_LENGTH];
                int err = 0;
                int *s = &err;
                read_all_teachers(db, list, s);
                if(err)
                    return;
                char SomeMsg[MSG_LENGTH];
                //all_teachers_to_html(list, result_msg);
                all_teachers_to_message(list, SomeMsg);
                resp_form(XML, SomeMsg, 200, result_msg);
                socket_write_string(clientSocket, result_msg);
            }
            else {
                char result_msg[MSG_LENGTH];
                resp_form(XML, NULL, 404, result_msg);
                socket_write_string(clientSocket, result_msg);
                return;
        }
    }
        else if(!strcmp(req.method, "DELETE"))
        {
            if(strcmp(req.uri, "/teachers/") > 0)
            {
                char result_msg[MSG_LENGTH];
                int err = 0;
                int *s = &err;
                read_all_teachers(db, list, s);
                if(err)
                    return;
                int pass = atoi(strtok(req.uri, "/teachers/"));
                teacher_t *t1 = new_teacher();
                int c = list_contains_passport(list, pass);
                if(c == -1)
                {
                    resp_form(XML, NULL, 404, result_msg);
                    socket_write_string(clientSocket, result_msg);
                    return;
                }
                list_remove(list, c);
                delete_teacher(db, pass, s);
                if(err)
                    return;
                resp_form(XML, "<message>"
                          "<text>Deletion succesfull!</text>"
                          "</message>", 200, result_msg);
                socket_write_string(clientSocket, result_msg);
            }
            else
            {
                char result_msg[MSG_LENGTH];
                resp_form(XML, NULL, 404, result_msg);
                socket_write_string(clientSocket, result_msg);
                return;
            }
        }
        else if(!strcmp(req.method, "POST"))
        {

            if(!strcmp(req.uri, "/teachers/"))
            {

                char result_msg[MSG_LENGTH];
                int passport = atoi(http_request_getArg(&req, "passport"));
                const char * fname = http_request_getArg(&req, "fname");
                const char * lname = http_request_getArg(&req, "lname");
                const char * birthdate = http_request_getArg(&req, "birthdate");
                double exp = atof(http_request_getArg(&req, "exp"));
                int  salary = atoi(http_request_getArg(&req, "salary"));
                int  group = atoi(http_request_getArg(&req, "group"));
                if(!passport || !fname || !lname || !birthdate || !exp || !salary || !group)
                {
                    char result_msg[MSG_LENGTH];
                    resp_form(XML, NULL, 403, result_msg);
                    socket_write_string(clientSocket, result_msg);
                    return;
                }
                if(exp < 0 || salary < 0)  //|| !date_check(birthdate)){
                {
                    char result_msg[MSG_LENGTH];
                    resp_form(XML, NULL, 403, result_msg);
                    socket_write_string(clientSocket, result_msg);
                    return;
                }
                teacher_t * t1 = new_teacher();
                t1->Passport = passport;
                t1->fname = fname;
                t1->lname = lname;
                t1->salary = salary;
                t1->exp = exp;
                t1->birthdate = birthdate;
                t1->group = group;
                int err_s = 0;
                int *err = &err_s;
                create_teacher(db, t1, err);
                if(err_s)
                {
                    return;
                }
                read_all_teachers(db, list, err);
                teacher_to_html(t1, result_msg);
                socket_write_string(clientSocket, result_msg);
            }
            else
            {
                char result_msg[MSG_LENGTH];
                resp_form(XML, NULL, 403, result_msg);
                socket_write_string(clientSocket, result_msg);
                return;
            }
        }
    else{
        char result_msg[MSG_LENGTH];
        resp_form(XML, NULL, 404, result_msg);
        socket_write_string(clientSocket, result_msg);
        return;
    }
}

int date_check(char *date)
{
    if(!date)
        return 0;
    if(strlen(date) != 10)
        return 0;
    char ybuf[2];
    char mbuf[2];
    char dbuf[2];
    for(int i = 0; i < 10; i++)
    {
        if(i == 4 || i == 7)
        {
            if(date[i] != '-')
            {
                return 0;
            }
        }
        else
        {
            if(!isdigit(date[i]))
                return 0;
            if(i < 4)
            {
                ybuf[i] = date[i];
            }
            else if(i < 7)
            {
                mbuf[i - 5] = date[i];
            }
            else
                dbuf[i - 8] = date[i];
        }
    }
    int yr = atoi(ybuf);
    int m = atoi(mbuf);
    int d = atoi(dbuf);
    if(yr < 1901 || m <= 0 || m > 12 || d <= 0)
        return 0;
    switch(m)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        if(d > 31)
            return 0;
    case 4:
    case 6:
    case 9:
    case 11:
        if(d > 30)
            return 0;
    case 2:
        if(yr % 4)
        {
            if(d > 28)
                return 0;
        }
        else
        {
            if(d > 29)
                return 0;
        }
    }
    return 1;
}
