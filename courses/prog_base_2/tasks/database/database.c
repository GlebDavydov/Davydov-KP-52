#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "database.h"

void print_teacher(teacher_t *self){
    printf("\nTeacher:\n\tPassport:\t\t%10d\n\tFirst name:\t\t%10s\n\tLast name:\t\t%10s\n\tSalary:\t\t\t%10d\n\tExperience, years:\t\t%.2f\n\tBirth date:\t\t%10s", self->Passport, self->fname, self->lname, self->salary, self->exp, self->birthdate);
}

void read_teacher(sqlite3 *db, int id, teacher_t *self, int *err){
    *err = 0;
    sqlite3_stmt *stmt = NULL;
    const char *sql = "SELECT * FROM teachers WHERE Passport = ?1;";
    int rc = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, id);
    if(SQLITE_OK != rc){
        *err = INVALID_REQUEST;
        return;
    }
    while(1){
        rc = sqlite3_step(stmt);
        if(SQLITE_ERROR == rc){
            *err = STEP_ERROR;
            return;
        }
        else {
            if(SQLITE_DONE == rc){
                printf("\nRead request processed.");
                break;
            }
            self->Passport = sqlite3_column_int(stmt, 0);
            strcpy(self->fname, (const char *)sqlite3_column_text(stmt, 1));
            strcpy(self->lname, (const char *)sqlite3_column_text(stmt, 2));
            self->salary = sqlite3_column_int(stmt, 3);
            self->exp = sqlite3_column_double(stmt, 4);
            strcpy(self->birthdate, (const char *)sqlite3_column_text(stmt, 5));
        }
    }
    sqlite3_finalize(stmt);
}

int create_teacher(sqlite3 *db, teacher_t *self, int *err){
    *err = 0;
    sqlite3_stmt *stmt = NULL;
    const char *sql;
    sql = "INSERT INTO teachers VALUES (?, ?, ?, ?, ?, ?);";
    int rc = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, self->Passport);
    sqlite3_bind_text(stmt, 2, self->fname, strlen(self->fname), SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, self->lname, strlen(self->lname), SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 4, self->salary);
    sqlite3_bind_double(stmt, 5, self->exp);
    sqlite3_bind_text(stmt, 6, self->birthdate, strlen(self->birthdate), SQLITE_TRANSIENT);
    if(SQLITE_OK != rc){
        *err = INVALID_REQUEST;
        return 0;
    } else if (SQLITE_DONE != (rc = sqlite3_step(stmt))){
        *err = PROCESS_FAILURE;
        return 0;
    }
    printf("\nCreate request processed.");
    sqlite3_finalize(stmt);
    return 1;
}

int delete_teacher(sqlite3 *db, int id, int *err){
    *err = 0;
    sqlite3_stmt *stmt = NULL;
    const char *sql = "DELETE FROM teachers WHERE Passport = ?;";
    int rc = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, id);
    if(SQLITE_OK != rc){
        *err = INVALID_REQUEST;
        return 0;
    } else if (SQLITE_DONE != (rc = sqlite3_step(stmt))){
        *err = PROCESS_FAILURE;
        return 0;
    }
    printf("\nDelete request processed.");
    sqlite3_finalize(stmt);
    return 1;
}

int update_teacher(sqlite3 *db, int id, teacher_t *self, int *err){
    *err = 0;
    sqlite3_stmt *stmt = NULL;
    const char *sql = "UPDATE teachers SET \"First Name\" = ?, \"Last Name\" = ?, Salary = ?, \"Experience years\" = ?, \"Birth date\" = ? WHERE Passport = ?;";
    int rc = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, self->fname, strlen(self->fname), SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, self->lname, strlen(self->lname), SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, self->salary);
    sqlite3_bind_double(stmt, 4, self->exp);
    sqlite3_bind_text(stmt, 5, self->birthdate, strlen(self->birthdate), SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 6, id);
    if(SQLITE_OK != rc){
        *err = INVALID_REQUEST;
        return 0;
    } else if (SQLITE_DONE != (rc = sqlite3_step(stmt))){
        *err = PROCESS_FAILURE;
        return 0;
    }
    printf("\nUpdate request processed.");
    sqlite3_finalize(stmt);
    return 1;
}

void select_teachers(sqlite3 *db, int filter1, double filter2, int *err){
    *err = 0;
    sqlite3_stmt *stmt = NULL;
    const char *sql = "SELECT * FROM teachers WHERE Salary < ?1 AND \"Experience years\" > ?2;";
    int rc = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, filter1);
    sqlite3_bind_double(stmt, 2, filter2);
    if(SQLITE_OK != rc){
        *err = INVALID_REQUEST;
        return;
    }
    while(1){
        rc = sqlite3_step(stmt);
        if(SQLITE_ERROR == rc){
            *err = STEP_ERROR;
            return;
        }
        else {
            teacher_t *self = malloc(sizeof(struct teacher_s));
            if(SQLITE_DONE == rc){
                printf("\nSelect request processed.");
                break;
            }
            self->Passport = sqlite3_column_int(stmt, 0);
            self->fname = (const char *)sqlite3_column_text(stmt, 1);
            self->lname = (const char *)sqlite3_column_text(stmt, 2);
            self->salary = sqlite3_column_int(stmt, 3);
            self->exp = sqlite3_column_double(stmt, 4);
            self->birthdate = (const char *)sqlite3_column_text(stmt, 5);
            print_teacher(self);
            free(self);
        }
    }
    sqlite3_finalize(stmt);
}

int teachers_count(sqlite3 *db, int *err){
    *err = 0;
    sqlite3_stmt *stmt = NULL;
    const char *sql = "SELECT * FROM teachers;";
    int rc = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
    if(SQLITE_OK != rc){
        *err = INVALID_REQUEST;
        return 0;
    }
    int count = 0;
    while(1){
        rc = sqlite3_step(stmt);
        if(SQLITE_ERROR == rc){
            *err = STEP_ERROR;
            return 0;
        }
        else {
            if(SQLITE_DONE == rc){
                printf("\nCount request processed.");
                break;
            }
            count++;
        }
    }
    sqlite3_finalize(stmt);
    return count;
}
