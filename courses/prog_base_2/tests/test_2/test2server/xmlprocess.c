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

/*char *teacher_to_message(teacher_t *self, int id){
    if(!self)
        return NULL;
    char buff[MSG_LENGTH];
    xmlDoc * doc = NULL;
	xmlNode * rootNode = NULL;
	xmlNode * teacherNode = NULL;
	xmlNode * cathedraNode = NULL;
    doc = xmlNewDoc("1.0");
	rootNode = xmlNewNode(NULL, "teachers");
	xmlDocSetRootElement(doc, rootNode);
	char strBuf[100];
	teacherNode = xmlNewChild(rootNode, NULL, "teacher", NULL);
	sprintf(strBuf, "%i", id);
	xmlNewChild(teacherNode, NULL, "id", strBuf);
	xmlNewChild(teacherNode, NULL, "firstName", self->name);
	xmlNewChild(teacherNode, NULL, "lastName", self->surname);
	xmlNewChild(teacherNode, NULL, "pensionDate", self->date);
	sprintf(strBuf, "%i", self->hours);
	xmlNewChild(teacherNode, NULL, "hours", strBuf);
	sprintf(strBuf, "%f", self->rating);
	xmlNewChild(teacherNode, NULL, "rating", strBuf);
	cathedraNode = xmlNewChild(teacherNode, NULL, "cathedra", NULL);
	xmlNewProp(cathedraNode, "name", self->cathedra->name);
	xmlNewChild(cathedraNode, NULL, "speciality", self->cathedra->speciality);
	xmlNewChild(cathedraNode, NULL, "group", self->cathedra->groups[0]);
	xmlNewChild(cathedraNode, NULL, "group", self->cathedra->groups[1]);
	xmlBuffer * bufferPtr = xmlBufferCreate();
	xmlNodeDump(bufferPtr, NULL, (xmlNode *)doc, 0, 1);
	sprintf(buff, "%s", (const char*)bufferPtr->content);
    xmlFreeDoc(doc);
	xmlCleanupParser();
	xmlBufferFree(bufferPtr);
    return buff;
}*/

/*char *all_teachers_to_message(list_t *list){
    if(list_count(list) == 0){
        return NULL;
    }
    char buff[MSG_LENGTH];
    xmlDoc * doc = NULL;
	xmlNode * rootNode = NULL;
    doc = xmlNewDoc("1.0");
	rootNode = xmlNewNode(NULL, "teachers");
	xmlDocSetRootElement(doc, rootNode);
	char strBuf[100];
    for(int i = 0; i  < list_count(list); i++){
        teacher_t *self = list_get(list, i);
        int id = list_id(list, i);
        xmlNode * teacherNode = NULL;
        xmlNode * cathedraNode = NULL;
        teacherNode = xmlNewChild(rootNode, NULL, "teacher", NULL);
        sprintf(strBuf, "%i", id);
        xmlNewChild(teacherNode, NULL, "id", strBuf);
        xmlNewChild(teacherNode, NULL, "firstName", self->name);
        xmlNewChild(teacherNode, NULL, "lastName", self->surname);
        xmlNewChild(teacherNode, NULL, "pensionDate", self->date);
        sprintf(strBuf, "%i", self->hours);
        xmlNewChild(teacherNode, NULL, "hours", strBuf);
        sprintf(strBuf, "%f", self->rating);
        xmlNewChild(teacherNode, NULL, "rating", strBuf);
        cathedraNode = xmlNewChild(teacherNode, NULL, "cathedra", NULL);
        xmlNewProp(cathedraNode, "name", self->cathedra->name);
        xmlNewChild(cathedraNode, NULL, "speciality", self->cathedra->speciality);
        xmlNewChild(cathedraNode, NULL, "group", self->cathedra->groups[0]);
        xmlNewChild(cathedraNode, NULL, "group", self->cathedra->groups[1]);
    }
	xmlBuffer * bufferPtr = xmlBufferCreate();
	xmlNodeDump(bufferPtr, NULL, (xmlNode *)doc, 0, 1);
	sprintf(buff, "%s", (const char*)bufferPtr->content);
    return buff;
}*/
