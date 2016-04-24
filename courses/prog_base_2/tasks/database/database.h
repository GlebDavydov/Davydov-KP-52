#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED

#include "sqlite3.h"

typedef struct teacher_s{
    int Passport;
    char *fname;
    char *lname;
    int salary;
    double exp;
    char *birthdate;
}teacher_t;

enum errors{STEP_ERROR, INVALID_REQUEST};

void print_teacher(teacher_t *self);
void read_teacher(sqlite3 *db, int id, teacher_t *self, int *err);
int create_teacher(sqlite3 *db, teacher_t *self, int *err);
int delete_teacher(sqlite3 *db, int id, int *err);
int update_teacher(sqlite3 *db, int id, teacher_t *self, int *err);
void select_teachers(sqlite3 *db, int filter1, double filter2, int *err);
int teachers_count(sqlite3 *db, int *err);


#endif // DATABASE_H_INCLUDED
