#ifndef TEXT_H_INCL
#define TEXT_H_INCL

enum err_codes{CORRECT = 0, NULL_POINTER = 1, TEXT_OVERFLOW, MEMORY_LACK, INCORRECT_INDEX, EMPTY_DELETION};

typedef char *sentence_t;
typedef struct text_s text_t;

text_t *text_new(int *ERR); //text.c
void text_free(text_t *ptext);
int text_isempty(text_t *ptext, int *ERR);
int text_word_number(text_t *ptext, int *ERR);
void text_print(text_t *ptext, int *ERR);
int text_count(text_t *ptext, int *ERR);

char *sentence_dot(char *pstr, int *ERR); //sentence.c
sentence_t sentence_create_beginning(text_t *ptext, char *sentence, int *ERR);
sentence_t sentence_create_end(text_t *ptext, char *sentence, int *ERR);
sentence_t sentence_create(text_t *ptext, int index, char *sentence, int *ERR);
void sentence_delete_beginning(text_t *ptext, int *ERR);
void sentence_delete_end(text_t *ptext, int *ERR);
void sentence_delete(text_t *ptext, int index, int *ERR);

int sentence_word_number(sentence_t curr_sentence, int *ERR); //sentence2.c
void sentence_print(sentence_t sentence);

#endif

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<ctype.h>

