#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libxml/parser.h>
#include <libxml/tree.h>

#include "teahers.h"

void print_teacher(teacher_t *self){
    printf("\tName:\t\t%10s\n\tSurname:\t%10s\n\tPension:\t%10s\n\tHours:\t%10d\n\tRating:\t%10.2f\n\tCathedra:\n\t\tName:\t%10s\n\t\tSpeciality:%10s\n\t\tGroups:\n\t\t\t%10s\n\t\t\t%10s\n", self->name, self->surname, self->date, self->hours, self->rating, self->cathedra->name, self->cathedra->speciality, self->cathedra->groups[0], self->cathedra->groups[1]);
}

void xml_out(char *text){
    xmlDoc * xDoc;
    xDoc = xmlReadMemory(text, strlen(text), NULL, NULL, 0);
    if(NULL == xDoc){
        printf("Error reading file");
        return;
    }
    xmlNode * xRootEl;
    xRootEl = xmlDocGetRootElement(xDoc);
    for(xmlNode * xCur = xRootEl->children; NULL != xCur ;xCur = xCur->next){
        if(XML_ELEMENT_NODE == xCur->type){
            printf("Tag name <%s>\n", xCur->name);
            for(xmlNode *xJ = xCur->children; xJ != NULL; xJ = xJ->next){
                if(XML_ELEMENT_NODE == xJ->type){
                    if(strcmp(xJ->name, "cathedra") == 0){
                        xmlNode *xCath = xJ;
                        char *name = xmlGetProp(xCath, "name");
                        printf("\t%10s: %s\n", xCath->name, name);
                        for(xmlNode *xGr = xCath->children->next; xGr != NULL; xGr = xGr->next){
                            if(XML_ELEMENT_NODE == xGr->type){
                                //!THE FOLLOWING CODE IS MORE CORRECT, BUT SLOWER AND WITH THE SAME RESULT XD
                                /*if(!strcmp(xGr->name, "groups")){
                                    printf("\t%10s:\n", xGr->name);
                                    for(xmlNode *xAgr = xGr->children->next; xAgr != NULL; xAgr = xAgr->next){
                                        if(XML_ELEMENT_NODE == xAgr->type){
                                            const char *content = xmlNodeGetContent(xAgr);
                                            printf("\t\t%s\n", content);
                                        }
                                    }
                                    continue;
                                }*/
                                const char *content = xmlNodeGetContent(xGr);
                                printf("\t%10s: %s\n", xGr->name, content);
                            }
                        }
                        continue;
                    }
                    const char *content = xmlNodeGetContent(xJ);
                    printf("\t%10s: %s\n", xJ->name, content);
                }
            }
        }
        printf("\n");
    }
}

int teachers_count(char *text){
    xmlDoc * xDoc;
    xDoc = xmlReadMemory(text, strlen(text), NULL, NULL, 0);
    if(NULL == xDoc){
        printf("Error reading file");
        return 0;
    }
    int count = 0;
    xmlNode * xRootEl;
    xRootEl = xmlDocGetRootElement(xDoc);
    for(xmlNode * xCur = xRootEl->children; NULL != xCur ;xCur = xCur->next){
        if(XML_ELEMENT_NODE == xCur->type){
            count++;
        }
    }
    return count;
}

void xml_extract(char *text, list_t *list){
    xmlDoc * xDoc;
    xDoc = xmlReadMemory(text, strlen(text), NULL, NULL, 0);
    if(NULL == xDoc){
        printf("Error reading file");
        return;
    }

    xmlNode * xRootEl;
    xRootEl = xmlDocGetRootElement(xDoc);
    int i = 0;
    for(xmlNode * xCur = xRootEl->children; NULL != xCur, i < teachers_count(text); xCur = xCur->next){
        if(XML_ELEMENT_NODE == xCur->type){
            teacher_t *teachers = new_teacher();
            //printf("Tag name <%s>\n", xCur->name);
            for(xmlNode *xJ = xCur->children; xJ != NULL; xJ = xJ->next){
                if(XML_ELEMENT_NODE == xJ->type){
                    if(!strcmp(xJ->name, "cathedra")){
                        xmlNode *xCath = xJ;
                        char *name = xmlGetProp(xCath, "name");
                        //printf("\t%10s: %s\n", xCath->name, name);
                        strcpy(teachers->cathedra->name, name);
                        for(xmlNode *xGr = xCath->children->next; xGr != NULL; xGr = xGr->next){
                            if(XML_ELEMENT_NODE == xGr->type){
                               if(!strcmp(xGr->name, "groups")){
                                    int j = 0;
                                    for(xmlNode *xAgr = xGr->children->next; xAgr != NULL; xAgr = xAgr->next){
                                        if(XML_ELEMENT_NODE == xAgr->type){
                                            if(!strcmp(xAgr->name, "group")){
                                                const char *content = xmlNodeGetContent(xAgr);
                                                teachers->cathedra->groups[j] = content;
                                                j++;
                                            }
                                        }
                                    }
                                    continue;
                                } else if(!strcmp(xGr->name, "speciality")){
                                    const char *content = xmlNodeGetContent(xGr);
                                    strcpy(teachers->cathedra->speciality, content);
                                }
                            }
                        }
                        continue;
                    }
                    else {
                        const char *content = xmlNodeGetContent(xJ);
                        if(!strcmp(xJ->name, "name")){
                            strcpy(teachers->name, content);
                        }
                        else if(!strcmp(xJ->name, "surname")){
                            strcpy(teachers->surname, content);
                        }
                        else if(!strcmp(xJ->name, "pension")){
                            strcpy(teachers->date, content);
                        }
                        else if(!strcmp(xJ->name, "hours")){
                            teachers->hours = atoi(content);
                        }
                        else if(!strcmp(xJ->name, "rating")){
                            teachers->rating = atof(content);
                        }
                    }
                }
            }
            i++;
            list_add(list, teachers);
        }
    }
}

char *teacher_to_message(teacher_t *self, int id){
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
}

char *all_teachers_to_message(list_t *list){
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
}
