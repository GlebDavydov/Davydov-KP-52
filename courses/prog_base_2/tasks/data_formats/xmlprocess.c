#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libxml/parser.h>
#include <libxml/tree.h>

#include "dataformats.h"

teacher_t *new_teacher(void){
    teacher_t *newTeacher = malloc(sizeof(struct teacher_s));
    newTeacher->cathedra = new_cathedra();
    return newTeacher;
}

cathedra_t *new_cathedra(void){
    cathedra_t *newCath = malloc(sizeof(struct cathedra_s));
    newCath->groups[0] = malloc(sizeof(char)*10);
    newCath->groups[1] = malloc(sizeof(char)*10);
    return newCath;
}

void free_teacher(teacher_t *self){
    free_cath(self->cathedra);
    free(self);
}

void free_cath(cathedra_t *self){
    free(self->groups[0]);
    free(self->groups[1]);
    free(self);
}

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

void xml_extract(char *text, int count, teacher_t teachers[count]){
    xmlDoc * xDoc;
    xDoc = xmlReadMemory(text, strlen(text), NULL, NULL, 0);
    if(NULL == xDoc){
        printf("Error reading file");
        return;
    }

    xmlNode * xRootEl;
    xRootEl = xmlDocGetRootElement(xDoc);
    /*teacher_t teachers[count];
    for(int i = 0; i < count; i++){
        teachers[i] = *new_teacher();
    }*/
    int i = 0;
    for(xmlNode * xCur = xRootEl->children; NULL != xCur, i < count; xCur = xCur->next){
        if(XML_ELEMENT_NODE == xCur->type){
            //printf("Tag name <%s>\n", xCur->name);
            for(xmlNode *xJ = xCur->children; xJ != NULL; xJ = xJ->next){
                if(XML_ELEMENT_NODE == xJ->type){
                    if(!strcmp(xJ->name, "cathedra")){
                        xmlNode *xCath = xJ;
                        char *name = xmlGetProp(xCath, "name");
                        //printf("\t%10s: %s\n", xCath->name, name);
                        strcpy(teachers[i].cathedra->name, name);
                        for(xmlNode *xGr = xCath->children->next; xGr != NULL; xGr = xGr->next){
                            if(XML_ELEMENT_NODE == xGr->type){
                               if(!strcmp(xGr->name, "groups")){
                                    int j = 0;
                                    for(xmlNode *xAgr = xGr->children->next; xAgr != NULL; xAgr = xAgr->next){
                                        if(XML_ELEMENT_NODE == xAgr->type){
                                            if(!strcmp(xAgr->name, "group")){
                                                const char *content = xmlNodeGetContent(xAgr);
                                                teachers[i].cathedra->groups[j] = content;
                                                j++;
                                            }
                                        }
                                    }
                                    continue;
                                } else if(!strcmp(xGr->name, "speciality")){
                                    const char *content = xmlNodeGetContent(xGr);
                                    strcpy(teachers[i].cathedra->speciality, content);
                                }
                            }
                        }
                        continue;
                    }
                    else {
                        const char *content = xmlNodeGetContent(xJ);
                        if(!strcmp(xJ->name, "name")){
                            strcpy(teachers[i].name, content);
                        }
                        else if(!strcmp(xJ->name, "surname")){
                            strcpy(teachers[i].surname, content);
                        }
                        else if(!strcmp(xJ->name, "pension")){
                            strcpy(teachers[i].date, content);
                        }
                        else if(!strcmp(xJ->name, "hours")){
                            teachers[i].hours = atoi(content);
                        }
                        else if(!strcmp(xJ->name, "rating")){
                            teachers[i].rating = atof(content);
                        }
                    }
                }
            }
            i++;
        }
    }
}
