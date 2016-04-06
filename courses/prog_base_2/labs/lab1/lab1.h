#ifndef LAB1_H_INCLUDED
#define LAB1_H_INCLUDED

enum ERROR_CODES{CORRECT = 0, NULL_POINTER, MEMORY_LACK, EMPTY_DELETION, SECTION_OVERFLOW, INCORRECT_NUMBER, BAD_NAME};

typedef struct section_s section_t;
typedef struct aud_s aud_t;

//section.c
section_t *section_new(int *ERR); //constructor
int section_isempty(section_t *psec, int *ERR);
int section_count(section_t *psec, int *ERR);
void section_free(section_t *victim, int *ERR); //destructor
void section_print_auditories(section_t *psec, int *ERR);
int section_total_places(section_t *psec, int *ERR);
aud_t *section_auditory_add(section_t *psec, int number, int places, int *ERR);
void section_auditory_remove(section_t *psec, int number, int *ERR); //auditory destructor
aud_t *section_auditory_find(section_t *psec, int number, int *ERR);

int auditory_saynumber(aud_t *paud, int *ERR);
int auditory_places(aud_t *paud, int *ERR);
int auditory_occupy(section_t *psec, int number, char *sname, int *ERR);
int auditory_deoccupy(section_t *psec, int number, int *ERR);
char *auditory_isoccupied(section_t *psec, int number, int *ERR);

int my_test(void);

#endif // LAB1_H_INCLUDED
