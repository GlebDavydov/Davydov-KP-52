#ifndef TEAHERS_H_INCLUDED
#define TEAHERS_H_INCLUDED


#define BUFFER_LENGTH 100000
#define MSG_LENGTH 10000
#define WORD_LENGTH 100

typedef struct list_s list_t;


typedef struct teacher_s{
    int Passport;
    char *fname;
    char *lname;
    int salary;
    double exp;
    char *birthdate;
}teacher_t;

//teachers_list
teacher_t *new_teacher(void);
void free_teacher(teacher_t *self);

list_t *list_new(void);
int list_add(list_t *base, teacher_t *self);
int list_find(list_t *base, teacher_t *self);
teacher_t *list_get(list_t *base, int index);
teacher_t *list_remove(list_t *base, int index);
void list_free(list_t *self);
int list_count(list_t *self);
int list_find_id(list_t *self, int id);
int list_id(list_t *self, int index);

//xmlproces
char *teacher_to_message(teacher_t *self, int id);
char *all_teachers_to_message(list_t *list);
char *me_to_message(void);
char *parse_response(char *stuff);


#endif // TEAHERS_H_INCLUDED
