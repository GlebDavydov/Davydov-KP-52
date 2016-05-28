#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
