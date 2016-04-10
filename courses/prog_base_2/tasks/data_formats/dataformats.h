#ifndef DATAFORMATS_H_INCLUDED
#define DATAFORMATS_H_INCLUDED

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

teacher_t *new_teacher(void);
cathedra_t *new_cathedra(void);

void free_teacher(teacher_t *self);
void free_cath(cathedra_t *self);

int teachers_count(char *text);
void xml_extract(char *text, int count, teacher_t teachers[count]);
void xml_out(char *text);
void print_teacher(teacher_t *self);

#endif // DATAFORMATS_H_INCLUDED
