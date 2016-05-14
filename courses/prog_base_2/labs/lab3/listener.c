#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "earthquake.h"

struct listener_s{
    char name[100];
    int events;
    seismometer_t *ssm;
    listener_t *next; //for linked list
};

listener_t *listener_new(char *name){
    listener_t *newListener = malloc(sizeof(struct listener_s));
    newListener->ssm = NULL;
    newListener->next = NULL;
    strcpy(newListener->name, name);
    newListener->events = 0;
    return newListener;
}

void listener_delete(listener_t * self){
    free(self);
}

seismometer_t *listener_get_ssm(listener_t * self){
    return self->ssm;
}

void listenet_set_ssm(listener_t *self, seismometer_t *ssm){
    self->ssm = ssm;
}

int get_event_status(listener_t *self){
    return self->events;
}

char *listener_get_name(listener_t *self){
    return self->name;
}

void listener_react_event(listener_t *self, message_callback cb, callback_args args){
    self->events++;
    printf("\n%s reports:", self->name);
    cb(args);
    printf("\n%s responded %d events", self->name, self->events);
}

listener_t *listener_get_next(listener_t *self){
    return self->next;
}

void listener_set_next(listener_t *self, listener_t *next){
    self->next = next;
}
