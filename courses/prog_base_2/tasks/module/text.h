#ifndef TEXT_H_INCL
#define TEXT_H_INCL

typedef char *sentence_t;
typedef struct text_s text_t;

text_t *text_new(void); //text.c
void text_free(text_t *ptext);
int text_isempty(text_t *ptext);
int text_word_number(text_t *ptext);
void text_print(text_t *ptext);

char *sentence_dot(char *pstr); //sentence.c
sentence_t sentence_create_beginning(text_t *ptext, char *sentence);
sentence_t sentence_create_end(text_t *ptext, char *sentence);
sentence_t sentence_create(text_t *ptext, int index, char *sentence);
void sentence_delete_beginning(text_t *ptext);
void sentence_delete_end(text_t *ptext);
void sentence_delete(text_t *ptext, int index);

int sentence_word_number(sentence_t curr_sentence); //sentence2.c
void sentence_print(sentence_t sentence);

#endif

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<ctype.h>

//#define ERROR_MESSAGE -1
