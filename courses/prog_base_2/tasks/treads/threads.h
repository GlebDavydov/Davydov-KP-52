#ifndef THREADS_H_INCLUDED
#define THREADS_H_INCLUDED

#include"thread.h"

typedef struct shared_s shared_t; //incapsulated

shared_t *new_shared(void); //constructor
void free_shared(shared_t *self); //destructor
void shared_unlock(shared_t *self);
void shared_lock(shared_t *self);
char get_symbol(shared_t *self); //getter
void change_symbol(shared_t *self, char symbol); //setter
void change_string(shared_t *self, char *str); //getter
char *get_string(shared_t *self); //setter

thread_t *readerThread(shared_t *shared);
thread_t *writerThread(shared_t *shared);

#endif // THREADS_H_INCLUDED
