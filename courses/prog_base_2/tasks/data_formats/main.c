#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dataformats.h"

int main() {
    char line[100];
    char text[10000] = "";
    FILE * fr = fopen("Teachers.xml", "r");
    while(fgets(line, 100, fr)){
    strcat(text, line);
    }

    //printf("%d", teachers_count(text));

    //xml_out(text);

    int c = teachers_count(text);
    teacher_t teachers[c];
    for(int i = 0; i < c; i++){
        teachers[i] = *new_teacher();
    }

    xml_extract(text, c, teachers);

    for(int i = 0; i < c; i++){
        printf("\nTeacher %d:\n", i);
        print_teacher(&teachers[i]);
        free_teacher(&teachers[i]);
    }
}

