#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "server.h"

int main(void){
    char line[100];
    char text[10000] = "";
    FILE * fr = fopen("Teachers.xml", "r");
    while(fgets(line, 100, fr)){
    strcat(text, line);
    }
    list_t *teachers = list_new();
    xml_extract(text, teachers);
    //xml_out(text);
    //teacher_update(list_get(teachers, 0), "name", "surname", "10.10.2001", 0, 0.0, "PZKS", "spec", "gr1", "gr2");
    http_request_startServer(teachers);
    list_free(teachers);
    return 0;
}
