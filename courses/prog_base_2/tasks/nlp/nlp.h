#ifndef NLP_H_INCLUDED
#define NLP_H_INCLUDED

#include<stdlib.h>

typedef struct text_s text_t;
typedef struct sent_s sent_t;
typedef struct word_s word_t;

text_t *text_new_empty(void);
text_t *read_text(char *filename);
void write_text(char *filename, text_t *self);
sent_t *sentense_new(char *contents);
char *print_sentense(char *buff, sent_t *self);
void sentense_free(sent_t *self);
void text_sentense_add(text_t *text, sent_t *self, int index);
sent_t *text_sentense_delete(text_t *self, int index);
word_t *word_new(char *contents);
void text_insertion_sort(text_t *self);
char* clear_odd(char *stuff, size_t length);
int text_sentenses(text_t *self);
int sentense_words(sent_t *self);
void text_free(text_t *self);


#endif // NLP_H_INCLUDED
