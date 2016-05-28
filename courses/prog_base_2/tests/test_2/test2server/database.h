#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED

#include "sqlite3.h"
#include "teahers.h"

enum errors{STEP_ERROR, INVALID_REQUEST, PROCESS_FAILURE};

void read_all_teachers(sqlite3 *db, list_t *list);
void read_teacher(sqlite3 *db, int id, teacher_t *self, int *err);
int create_teacher(sqlite3 *db, teacher_t *self, int *err);
int delete_teacher(sqlite3 *db, int id, int *err);
int update_teacher(sqlite3 *db, int id, teacher_t *self, int *err);
void select_teachers(sqlite3 *db, int filter1, double filter2, int *err);
int teachers_count(sqlite3 *db, int *err);


#endif // DATABASE_H_INCLUDED
