#ifndef TEACHERS_H_INCLUDED
#define TEACHERS_H_INCLUDED

typedef struct teacher_s teacher_t;

teacher_t *teacher_new_defaults(void);
void teacher_free(teacher_t *self);
char *teacher_get_fname(teacher_t *self);
char *teacher_get_lname(teacher_t *self);
int teacher_get_experience(teacher_t *self);
int teacher_get_salary(teacher_t *self);
void teacher_set_fname(teacher_t *self, char *fname);
void teacher_set_lname(teacher_t *self, char *lname);
void teacher_set_experience(teacher_t *self, int exp);
void teacher_set_salary(teacher_t *self, int money);

#endif // TEACHERS_H_INCLUDED
