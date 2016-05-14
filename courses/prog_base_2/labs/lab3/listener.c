#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "earthquake.h"

struct listener_s{
    char name[100];
    int events;
};

listener_t *listener_new(char *name){
    listener_t *newListener = malloc(sizeof(struct listener_s));
    strcpy(newListener->name, name);
    newListener->events = 0;
    return newListener;
}

void listener_delete(listener_t * self){
    free(self);
}

char *listener_get_name(listener_t *self){
    return self->name;
}

void calm(listener_t *self ,callback_args args){
    self->events++;
    printf("\n%s reports:", self->name);
    char *sendername = args;
    printf("\n\"%s\" registering high seismic activity warning! Earthquake possible. Evacuation recommended!", sendername);
    printf("\n%s responded %d events", self->name, self->events);
}

void panic(listener_t *self ,callback_args args){
    self->events++;
    printf("\n%s reports:", self->name);
    char *sendername = args;
    printf("\n\t\t\t******WARNING!!!******\n\"%s\" registering extreme seismic activity! Earthquake is imminent! Evacuation is NECESSARY!", sendername);
    printf("\n%s responded %d events", self->name, self->events);
}


