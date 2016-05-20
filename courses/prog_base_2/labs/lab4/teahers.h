#ifndef TEAHERS_H_INCLUDED
#define TEAHERS_H_INCLUDED


#define BUFFER_LENGTH 100000
#define MSG_LENGTH 10000
#define WORD_LENGTH 100

typedef struct list_s list_t;

typedef struct cathedra_s{
    char name[10];
    char speciality[20];
    char *groups[2];
}cathedra_t;

typedef struct teacher_s{
    char name[30];
    char surname[30];
    char date[20];
    int hours;
    double rating;
    cathedra_t *cathedra;
} teacher_t;

//teachers_list
void teacher_update(teacher_t *self, char *fname, char *lname, char *date, int hours, double rating, char *cname, char *sname, char *gname1, char *gname2);
teacher_t *new_teacher(void);
cathedra_t *new_cathedra(void);
void free_teacher(teacher_t *self);
void free_cath(cathedra_t *self);

list_t *list_new(void);
int list_add(list_t *base, teacher_t *self);
int list_find(list_t *base, teacher_t *self);
teacher_t *list_get(list_t *base, int index);
teacher_t *list_remove(list_t *base, int index);
void list_free(list_t *self);
int list_count(list_t *self);
int list_find_id(list_t *self, int id);
int list_id(list_t *self, int index);

//xmlprocess
int teachers_count(char *text);
void xml_extract(char *text, list_t *list);
void xml_out(char *text);
void print_teacher(teacher_t *self);
char* teacher_to_message(teacher_t *self, int id);
char* all_teachers_to_message(list_t *list);

#endif // TEAHERS_H_INCLUDED
