#include <stdlib.h>
#include <string.h>

#include "teachers.h"

struct teacher_s{
    char first_name[30];
    char last_name[30];
    int experience;
    int salary;
};

teacher_t *teacher_new_defaults(void){
    teacher_t *newTeacher = malloc(sizeof(struct teacher_s));
    strcpy(newTeacher->first_name, "DefaultFirstName");
    strcpy(newTeacher->last_name, "DefaultLastName");
    newTeacher->experience = 0;
    newTeacher->salary = 1366;
    return newTeacher;
}

void teacher_free(teacher_t *self){
    free(self);
}

char *teacher_get_fname(teacher_t *self){
    char *buffer = malloc((sizeof(char))*30);
    strcpy(buffer, self->first_name);
    return buffer;
}

char *teacher_get_lname(teacher_t *self){
    char *buffer = malloc((sizeof(char))*30);
    strcpy(buffer, self->last_name);
    return buffer;
}

int teacher_get_experience(teacher_t *self){
    return self->experience;
}

int teacher_get_salary(teacher_t *self){
    return self->salary;
}

void teacher_set_fname(teacher_t *self, char *fname){
    if(strlen(fname) < 30)
        strcpy(self->first_name, fname);
}

void teacher_set_lname(teacher_t *self, char *lname){
    if(strlen(lname) < 30)
        strcpy(self->last_name, lname);
}

void teacher_set_experience(teacher_t *self, int exp){
    self->experience = exp;
}

void teacher_set_salary(teacher_t *self, int money){
    self->salary = money;
}

