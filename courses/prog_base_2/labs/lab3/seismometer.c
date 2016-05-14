#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "earthquake.h"



double get_random_number(void);

struct seismometer_s{
    int status;
    int count;
    char name[50];
    event_t *first;
};

struct event_s{
    event_t *next;
    listener_t *self;
    message_callback cb;
};

event_t *event_new(listener_t *self, message_callback cb){
    event_t *eve = malloc(sizeof(struct event_s));
    eve->cb = cb;
    eve->self = self;
    eve->next = NULL;
    return eve;
}

seismometer_t *ssm_new(char *name){
    seismometer_t *newSsm = malloc(sizeof(struct seismometer_s));
    newSsm->status = OFF;
    newSsm->count = 0;
    newSsm->first = NULL;
    strcpy(newSsm->name, name);
    return newSsm;
}

void ssm_delete(seismometer_t *self){
    free(self);
}

int ssm_add_listener(seismometer_t *base, listener_t *self, message_callback cb){
    if(base->count > 256){
        printf("\nToo many listeners at this seismo!");
        return 0;
    }
    if(!self)
        return 0;
    event_t *eve = event_new(self, cb);
    if(base->count == 0){
        base->first = eve;
        base->count++;
    }
    else{
        event_t *temp = base->first;
        char *name = listener_get_name(self);
        if(!strcmp(name, listener_get_name(temp->self))){
            printf("\nListener with such a name already exists!");
            return 0;
        }
        while(temp->next){
        temp = temp->next;
            if(!strcmp(name, listener_get_name(temp->self))){
                printf("\nListener with such a name already exists!");
                return 0;
            }
        }
        temp->next = eve;
        base->count++;
    }
    return 1;
}

int ssm_get_listener_index(seismometer_t * self, char * name){
    event_t *temp = self->first;
    for(int i = 0; temp; i++){
        if(!strcmp(name, listener_get_name(temp->self))){
            return i;
        }
        temp = temp->next;
    }
    return ERR_INDEX;
}

listener_t *ssm_remove_listener(seismometer_t *self, listener_t *lis){
    int index = ssm_get_listener_index(self, listener_get_name(lis));
    if(index == ERR_INDEX){
        printf("\nNo such index!");
        return NULL;
    }
    event_t *temp1 = self->first;
    if(!temp1){
        return NULL;
    }
    if(index == 0){
        self->first = temp1->next;
        self->count--;
        listener_t *list1 = temp1->self;
        free(temp1);
        return list1;
    }
    for(int i = 1; i < index; i++){
        temp1 = temp1->next;
    }
    event_t *temp2 = temp1->next;
    temp1->next = temp2->next;
    self->count--;
    listener_t *list1 = temp2->self;
    free(temp2);
    return list1;
}

void ssm_send_event(seismometer_t *self){
    event_t *eve = self->first;
    while(eve){
        eve->cb(eve->self, self->name);
        eve = eve->next;
    }
}

void ssm_cycle(seismometer_t *self, ssm_mode cb){
    if(self->status == OFF){
        printf("\nSeismometer off. No monitoring possible");
        return;
    }
    printf("\nStarting monitoring.");
    int counter = 0;
    int status = CLEAR;
    double random;
    while(1){
        while(!kbhit()){
            random = get_random_number();
            cb(random);
            if(random >= 5.0){
                if(status != HIGHS){
                    status = HIGHS;
                    counter = 1;
                } else
                    counter++;
            } else {
                counter = 0;
                status = CLEAR;
            }
            if(counter == 3){
                ssm_send_event(self);
                counter = 0;
            }
        }
        if(ESCAPE == getch())
            break;
    }
    printf("\nMonitoring over.");
}

void ssm_turn_on(seismometer_t *self){
    printf("\nSeismo \"%s\" on alert", self->name);
    self->status = ON;
}

void ssm_turn_off(seismometer_t *self){
    printf("\nSeismo \"%s\" deactivated", self->name);
    self->status = OFF;
}

double get_random_number(void){
    int stuff = rand()%1001;
    return (double)stuff/100;
}


int ssm_get_status(seismometer_t *self){
    return self->status;
}

int ssm_get_count(seismometer_t *self){
    return self->count;
}

char *ssm_get_name(seismometer_t *self){
    return self->name;
}

