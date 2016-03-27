#include<stdlib.h>

#include"threads.h"

//#include"thread.h"
#include"mutex.h"

struct shared_s{
    mutex_t *mut;
    char content;
    char *string;
};

void change_string(shared_t *self, char *str){
    self->string = str;
}

char *get_string(shared_t *self){
    return self->string;
}

shared_t *new_shared(void){
    shared_t *newchar = malloc(sizeof(struct shared_s));
    newchar->mut = mutex_new();
    return newchar;
}

void free_shared(shared_t *self){
    mutex_free(self->mut);
    free(self);
}

void shared_unlock(shared_t *self){
    mutex_unlock(self->mut);
}

void shared_lock(shared_t *self){
    mutex_lock(self->mut);
}

char get_symbol(shared_t *self){
    return self->content;
}

void change_symbol(shared_t *self, char symbol){
    self->content = symbol;
}
