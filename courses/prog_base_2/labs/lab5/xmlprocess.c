#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <libxml/parser.h>
#include <libxml/tree.h>

#include "teahers.h"

char *me_to_message(void){
    xmlDoc *doc = NULL;
    xmlNode * rootNode = NULL;
    xmlNode *textNode = NULL;
    doc = xmlNewDoc("1.0");
    rootNode = xmlNewNode(NULL, "message");
    xmlDocSetRootElement(doc, rootNode);
    char buff[1000];
    xmlNewChild(rootNode, NULL, "status", "OK");
    textNode = xmlNewChild(rootNode, NULL, "text", NULL);
    xmlNewChild(textNode, NULL, "student", "Gleb Davydov");
    xmlNewChild(textNode, NULL, "group", "KP-52");
    xmlNewChild(textNode, NULL, "variant", "24");
    xmlBuffer * bufferPtr = xmlBufferCreate();
	xmlNodeDump(bufferPtr, NULL, (xmlNode *)doc, 0, 1);
	sprintf(buff, "%s", (const char*)bufferPtr->content);
    xmlFreeDoc(doc);
	xmlCleanupParser();
	xmlBufferFree(bufferPtr);
    return buff;
}

char *parse_response(char *stuff){
    char author[100];
    char book[100];
    xmlDoc *rcv = xmlReadMemory(stuff, strlen(stuff), NULL, NULL, 0);
    xmlDoc *rst = xmlNewDoc("1.0");
    xmlNode *respRootNode = xmlNewNode(NULL, "message");
    xmlDocSetRootElement(rst, respRootNode);
    char buff[1000];
    xmlNewChild(respRootNode, NULL, "status", "OK");
    xmlNode *textNode = NULL;
    textNode = xmlNewChild(respRootNode, NULL, "text", NULL);
    xmlNode * xRootEl;
    xRootEl = xmlDocGetRootElement(rcv);
    for(xmlNode * xCur = xRootEl->children; NULL != xCur ;xCur = xCur->next){
        const char *name = xCur->name;
        const char *content = xmlNodeGetContent(xCur);
        xmlNewChild(textNode, NULL, name, content);
    }
    time_t ptimer;
	struct tm *cl1 = malloc(sizeof(struct tm));
	cl1 = localtime(&ptimer);
    xmlNewChild(textNode, NULL, "recieving_time", asctime(cl1));
    xmlBuffer * bufferPtr = xmlBufferCreate();
	xmlNodeDump(bufferPtr, NULL, (xmlNode *)rst, 0, 1);
	sprintf(buff, "%s", (const char*)bufferPtr->content);
    xmlFreeDoc(rst);
    xmlFreeDoc(rcv);
	xmlCleanupParser();
	xmlBufferFree(bufferPtr);
    return buff;
}

char *teacher_to_message(teacher_t *self, int id, char *buff){
    if(!self)
        return NULL;
    xmlDoc * doc = NULL;
	xmlNode * rootNode = NULL;
	xmlNode *textNode = NULL;
	xmlNode * teacherNode = NULL;
    doc = xmlNewDoc("1.0");
	rootNode = xmlNewNode(NULL, "Message");
	xmlDocSetRootElement(doc, rootNode);
	textNode = xmlNewChild(rootNode, NULL, "text", NULL);
	xmlDocSetRootElement(doc, rootNode);
	char strBuf[100];
    teacherNode = xmlNewChild(textNode, NULL, "teacher", NULL);
    sprintf(strBuf, "%d", self->Passport);
    xmlNewChild(teacherNode, NULL, "Passport", strBuf);
    xmlNewChild(teacherNode, NULL, "Name", self->fname);
    xmlNewChild(teacherNode, NULL, "Surname", self->lname);
    sprintf(strBuf, "%d", self->salary);
    xmlNewChild(teacherNode, NULL, "Salary", strBuf);
    sprintf(strBuf, "%.2f", self->exp);
    xmlNewChild(teacherNode, NULL, "Experience", strBuf);
    xmlNewChild(teacherNode, NULL, "Birthdate", self->birthdate);
    sprintf(strBuf, "%d", self->group);
    xmlNewChild(teacherNode, NULL, "Group", strBuf);
    xmlNewChild(teacherNode, NULL, "Starosta", self->starosta);
	xmlBuffer * bufferPtr = xmlBufferCreate();
	xmlNodeDump(bufferPtr, NULL, (xmlNode *)doc, 0, 1);
	sprintf(buff, "%s", (const char*)bufferPtr->content);
    xmlFreeDoc(doc);
	xmlCleanupParser();
	xmlBufferFree(bufferPtr);
    return buff;
}


char *all_teachers_to_message(list_t *list, char *buff){
    if(list_count(list) == 0){
        return NULL;
    }
    xmlDoc * doc = NULL;
	xmlNode * rootNode = NULL;
	xmlNode *textNode = NULL;
    doc = xmlNewDoc("1.0");
	rootNode = xmlNewNode(NULL, "Message");
	xmlDocSetRootElement(doc, rootNode);
	textNode = xmlNewChild(rootNode, NULL, "text", NULL);
	char strbuf[100];
    for(int i = 0; i  < list_count(list); i++){
        teacher_t *self = list_get(list, i);
        xmlNode * teacherNode = NULL;
        teacherNode = xmlNewChild(textNode, NULL, "teacher", NULL);
        sprintf(strbuf, "%d", self->Passport);
        xmlNewChild(teacherNode, NULL, "Passport", strbuf);
        xmlNewChild(teacherNode, NULL, "Name", self->fname);
        xmlNewChild(teacherNode, NULL, "Surname", self->lname);
        sprintf(strbuf, "%d", self->salary);
        xmlNewChild(teacherNode, NULL, "Salary", strbuf);
        sprintf(strbuf, "%.2f", self->exp);
        xmlNewChild(teacherNode, NULL, "Experience", strbuf);
        xmlNewChild(teacherNode, NULL, "Birthdate", self->birthdate);
        sprintf(strbuf, "%d", self->group);
        xmlNewChild(teacherNode, NULL, "Group", strbuf);
        xmlNewChild(teacherNode, NULL, "Starosta", self->starosta);
    }
	xmlBuffer * bufferPtr = xmlBufferCreate();
	xmlNodeDump(bufferPtr, NULL, (xmlNode *)doc, 0, 1);
	sprintf(buff, "%s\0", (const char*)bufferPtr->content);
    return buff;
}

char *teacher_to_html(teacher_t *self, char *buff){
    sprintf(buff, "<!DOCTYPE html>"
"<html>"
    "<head>"
        "<title>KPI FPM TDB</title>"
    "</head>"
    "<body>"
        "<h3>%s %s</h3>"
        "<table>"
            "<tr>"
                "<th>Passport:</th>"
                "<th>Experience:</th>"
                "<th>Salary:</th>"
                "<th>Birthdate:</th>"
                "<th>Group:</th>"
                "<th>Starosta:</th>"
            "</tr>"
            "<tr>"
                "<th>%d</th>"
                "<th>%.2f</th>"
                "<th>%d</th>"
                "<th>%s</th>"
                "<th>%d</th>"
                "<th>%s</th>"
            "</tr>"
        "</table>"
        "<a href=\"#\" onclick=\"doDelete()\">Delete</a>"
        "<br>"
        "<a href=\"/\">Home</a>"
        "<script>"
            "function doDelete() {"
                "var xhttp = new XMLHttpRequest();"
                "xhttp.open(\"DELETE\", \"http://127.0.0.1:5000/teachers/%d\", true);"
                "xhttp.send();"
            "}"
        "</script>"
    "</body>"
"</html>", self->fname, self->lname, self->Passport, self->exp, self->salary, self->birthdate, self->group, self->starosta, self->Passport);
}

char *all_teachers_to_html(list_t *list, char *buff){
    char tmpBuff[10000];
    sprintf(tmpBuff, "<table>"
                        "<caption>OUR BEST</caption>"
        "<tr>"
            "<th>Id</th>"
            "<th>First Name</th>"
            "<th>Last Name</th>"
	"</tr>");
                for(int i = 0; i < list_count(list); i++){
                    teacher_t *t1 = list_get(list, i);
                    sprintf(tmpBuff, "%s"
    "<tr>"
		"<th><a href=\"/teachers/%d\">%d</a></th>"
		"<th>%s</th>"
		"<th>%s</th>"
	"</tr>", tmpBuff, t1->Passport, t1->Passport, t1->fname, t1->lname);
                }
                    sprintf(buff,
                        "<!DOCTYPE html>"
"<html>"
    "<head>"
        "<title>KPI FPM TDB</title>"
    "</head>"
    "<body>"

            "<h3>ALL TEACHERS</h3>"
            "%s"
            "</table>"
            "<br>"
            "<br>"
            "<a href=\"/teachers/new\">New person</a>"


    "</body>"
"</html>"
                        /*"HTTP/1.1 200 OK\n"
                        "Content-length: %zu\n"
                        "Content-type: application/xml\n"
                        "\n"
                        "%s\0",
                        strlen(all_teachers_to_message(list)), all_teachers_to_message(list)*/, tmpBuff);
}
