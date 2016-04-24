#include <stdio.h>
#include <stdlib.h>

#include "database.h"

int err_proc(int *err){
    if(*err){
        if(*err == INVALID_REQUEST){
            printf("\nError: invalid request.");
        } else if(*err == STEP_ERROR){
            printf("\nStep error.");
        }
        return(1);
    }
    return 0;
}

int main(void){
    sqlite3 *db;
    int rc = 0;
    rc = sqlite3_open("teachers.db", &db);
    if(SQLITE_OK != rc){
        printf("Error: couldn't open database");
        return(1);
    }
    int err_status = 0;
    int *err = &err_status;
    teacher_t *t1 = malloc(sizeof(struct teacher_s));
    t1->Passport = 1010;
    t1->fname = "Donkey";
    t1->lname = "Kong";
    t1->salary = 0;
    t1->exp = 2.1;
    t1->birthdate = "1969.01.01";
    create_teacher(db, t1, err);
    if(err_proc(err))
        return(1);
    teacher_t *t2 = malloc(sizeof(struct teacher_s));
    t2->fname = malloc(1000);
    t2->lname = malloc(1000);
    t2->birthdate = malloc(1000);
    printf("\nTeachers: %d", teachers_count(db, err));
    if(err_proc(err))
        return(1);
    read_teacher(db, 1, t2, err);
    if(err_proc(err))
        return(1);
    print_teacher(t2);
    t1->salary += 2000;
    update_teacher(db, 1, t1, err);
    if(err_proc(err))
        return(1);
    delete_teacher(db, 1, err);
    if(err_proc(err))
        return(1);
    printf("\nTeachers: %d", teachers_count(db, err));
    if(err_proc(err))
        return(1);
    free(t1);
    free(t2->fname);
    free(t2->lname);
    free(t2->birthdate);
    free(t2);
    select_teachers(db, 3367, 0.0, err);
    if(err_proc(err))
        return(1);
    sqlite3_close(db);
    free(db);
    return 0;
}
