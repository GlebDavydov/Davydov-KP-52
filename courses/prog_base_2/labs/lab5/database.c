#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "teahers.h"
#include "database.h"

void group_fill(teacher_t *self, sqlite3*db, int grname){
    sqlite3_stmt *stmt = NULL;
    const char *sql = "SELECT * FROM groups WHERE number = ?1;";
    int rc = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, grname);
    if(SQLITE_OK != rc){
        self->group = 0;
        strcpy(self->starosta, " ");
        return;
    }
    while(1){
        rc = sqlite3_step(stmt);
        if(SQLITE_ERROR == rc){
            return;
        }
        else {
            if(SQLITE_DONE == rc){
                printf("\nRead request processed.");
                break;
            }
            self->group = sqlite3_column_int(stmt, 0);
            strcpy(self->starosta, (const char *)sqlite3_column_text(stmt, 1));
        }
    }
    sqlite3_finalize(stmt);
}

/*void group_new(teacher_t *self, sqlite3*db){
    sqlite3_stmt *stmt = NULL;
    const char *sql = "INSERT INTO groups VALUES (?, ?);";
    int rc = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, self->group);
    sqlite3_bind_text(stmt, 2, self->starosta, strlen(self->starosta), SQLITE_TRANSIENT);
    if(SQLITE_OK != rc){
        return;
    } else if (SQLITE_DONE != (rc = sqlite3_step(stmt))){
        return;
    }
    sqlite3_finalize(stmt);
    return 1;
}*/

void read_all_teachers(sqlite3 *db, list_t *list, int *err){
    *err = 0;
    sqlite3_stmt *stmt = NULL;
    const char *sql = "SELECT * FROM teachers;";
    int rc = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
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
            teacher_t *self = new_teacher();
            self->Passport = sqlite3_column_int(stmt, 0);
            strcpy(self->fname, (const char *)sqlite3_column_text(stmt, 1));
            strcpy(self->lname, (const char *)sqlite3_column_text(stmt, 2));
            self->salary = sqlite3_column_int(stmt, 3);
            self->exp = sqlite3_column_double(stmt, 4);
            strcpy(self->birthdate, (const char *)sqlite3_column_text(stmt, 5));
            group_fill(self, db, sqlite3_column_int(stmt, 6));
            int c = list_contains_passport(list, self->Passport);
            if(c != -1)
                list_remove(list, c);
            list_add(list, self);
        }
    }
    sqlite3_finalize(stmt);
}

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
            group_fill(self, db, sqlite3_column_int(stmt, 6));
        }
    }
    sqlite3_finalize(stmt);
}

int create_teacher(sqlite3 *db, teacher_t *self, int *err){
    *err = 0;
    sqlite3_stmt *stmt = NULL;
    const char *sql;
    sql = "INSERT INTO teachers VALUES (?, ?, ?, ?, ?, ?, ?);";
    int rc = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, self->Passport);
    sqlite3_bind_text(stmt, 2, self->fname, strlen(self->fname), SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, self->lname, strlen(self->lname), SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 4, self->salary);
    sqlite3_bind_double(stmt, 5, self->exp);
    sqlite3_bind_text(stmt, 6, self->birthdate, strlen(self->birthdate), SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 7, self->group);
    if(SQLITE_OK != rc){
        *err = INVALID_REQUEST;
        return 0;
    } else if (SQLITE_DONE != (rc = sqlite3_step(stmt))){
        *err = PROCESS_FAILURE;
        return 0;
    }
    //group_new(self, db);
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

void select_teachers(sqlite3 *db, list_t * list, int filter1, double filter2, int *err, int state){
    *err = 0;
    sqlite3_stmt *stmt = NULL;
    const char *sql = malloc(1000);
    switch(state){
case 3:
    sprintf(sql, "SELECT * FROM teachers WHERE Salary > ?1 AND \"Experience years\" = ?2;");
    break;
case 5:
    sprintf(sql, "SELECT * FROM teachers WHERE Salary < ?1 AND \"Experience years\" = ?2;");
    break;
case 7:
    sprintf(sql, "SELECT * FROM teachers WHERE Salary = ?1 AND \"Experience years\" > ?2;");
    break;
case 11:
    sprintf(sql, "SELECT * FROM teachers WHERE Salary = ?1 AND \"Experience years\" < ?2;");
    break;
case 21:
    sprintf(sql, "SELECT * FROM teachers WHERE Salary > ?1 AND \"Experience years\" > ?2;");
    break;
case 35:
    sprintf(sql, "SELECT * FROM teachers WHERE Salary < ?1 AND \"Experience years\" > ?2;");
    break;
case 33:
    sprintf(sql, "SELECT * FROM teachers WHERE Salary > ?1 AND \"Experience years\" < ?2;");
    break;
case 55:
    sprintf(sql, "SELECT * FROM teachers WHERE Salary < ?1 AND \"Experience years\" < ?2;");
    break;
    case 1:
    default:
        sprintf(sql, "SELECT * FROM teachers WHERE Salary = ?1 AND \"Experience years\" = ?2;");
        break;
    }
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
            if(SQLITE_DONE == rc){
                printf("\nSelect request processed.");
                break;
            }
            teacher_t *self = new_teacher();
            self->Passport = sqlite3_column_int(stmt, 0);
            strcpy(self->fname, (const char *)sqlite3_column_text(stmt, 1));
            strcpy(self->lname, (const char *)sqlite3_column_text(stmt, 2));
            self->salary = sqlite3_column_int(stmt, 3);
            self->exp = sqlite3_column_double(stmt, 4);
            strcpy(self->birthdate, (const char *)sqlite3_column_text(stmt, 5));
            group_fill(self, db, sqlite3_column_int(stmt, 6));
            int c = list_contains_passport(list, self->Passport);
            if(c != -1)
                list_remove(list, c);
            list_add(list, self);
        }
    }
    free(sql);
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



