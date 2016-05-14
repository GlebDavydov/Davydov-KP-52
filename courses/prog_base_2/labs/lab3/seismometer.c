#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "earthquake.h"

#define OFF 0
#define ON 1
#define ESCAPE 27

enum events{NOTHING, SWITCHED_OFF, SWITCHED_ON, ZERO_ACTIVITY, EARTHQUAKE, CRITICAL_EARHQUAKE};
enum status{CLEAR, ZEROS, HIGHS, VHIGHS};


double get_random_number(void);
listener_t *listener_get_next(listener_t *self);
void listener_set_next(listener_t *self, listener_t *next); // for linked list

struct seismometer_s{
    int status;
    int count;
    int event;
    listener_t *first;
};

void swon(void){
printf("\nSeismometer swiched on. System on full alert");}
void swoff(void){
printf("\nSeismometer swiched off. Monitoring over");}
void zeroact(void){
printf("\nRegistering no seismic activity");}
void earthquake(void){
printf("\nHigh seismic activity warning! Earthquake possible. Evacuation recommended!");}
void earthquake_critical(void){
printf("\n\t\t\t******WARNING!!!******\nExtreme seismic activity! Earthquake is imminent! Evacuation is NECESSARY!");}


seismometer_t *ssm_new(void){
    seismometer_t *newSsm = malloc(sizeof(struct seismometer_s));
    newSsm->status = OFF;
    newSsm->count = 0;
    newSsm->first = NULL;
    return newSsm;
}

void ssm_delete(seismometer_t *self){
    free(self);
}

int ssm_add_listener(seismometer_t *base, listener_t *self){
    if(base->count > 256){
        printf("\nToo many listeners at this seismo!");
        return 0;
    }
    if(!self)
        return 0;
    if(base->count == 0){
        base->first = self;
        listener_set_next(self, NULL);
        base->count++;
    }
    else{
        listener_t *temp = base->first;
        char *name = listener_get_name(self);
        if(!strcmp(name, listener_get_name(temp))){
            printf("\nListener with such a name already exists!");
            return 0;
        }
        while(listener_get_next(temp)){
        temp = listener_get_next(temp);
            if(!strcmp(name, listener_get_name(temp))){
                printf("\nListener with such a name already exists!");
                return 0;
            }
        }
        listener_set_next(temp, self);
        listener_set_next(self, NULL);
        base->count++;
    }
    return 1;
}

int ssm_get_listener_index(seismometer_t * self, char * name){
    listener_t *temp = self->first;
    for(int i = 0; temp; i++){
        if(!strcmp(name, listener_get_name(temp))){
            return i;
        }
        temp = listener_get_next(temp);
    }
    return ERR_INDEX;
}

listener_t *ssm_remove_listener(seismometer_t *self, int index){
    if(index < 0 || index >= self->count){
        printf("\nNo such index!");
        return NULL;
    }
    listener_t *temp1 = self->first;
    if(!temp1){
        return NULL;
    }
    if(index == 0){
        self->first = listener_get_next(temp1);
        self->count--;
        return temp1;
    }
    for(int i = 1; i < index; i++){
        temp1 = listener_get_next(temp1);
    }
    listener_t *temp2 = listener_get_next(temp1);
    listener_set_next(temp1, listener_get_next(temp2));
    self->count--;
    return temp2;
}

void ssm_send_event(seismometer_t *self){
    if(self->count == 0){
        return;
    }
    message_callback cb;
    switch(self->event){
        case SWITCHED_ON:
            cb = swon;
            break;
        case SWITCHED_OFF:
            cb = swoff;
            break;
        case ZERO_ACTIVITY:
            cb = zeroact;
            break;
        case EARTHQUAKE:
            cb = earthquake;
            break;
        case CRITICAL_EARHQUAKE:
            cb = earthquake_critical;
            break;
        case NOTHING:
        default:
            return;
    }
    listener_t *temp = self->first;
    while(temp){
        listener_react_event(temp, cb);
        temp = listener_get_next(temp);
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
            if(random <= 2.0){
                if(status != ZEROS){
                    status = ZEROS;
                    counter = 1;
                }
                else{
                    counter++;
                }
            }
            else if(random >= 6.0){
                if(status != HIGHS && status != VHIGHS){
                    counter = 0;
                }
                if(random >= 8.5){
                    status = VHIGHS;
                }
                if(status != VHIGHS){
                    status = HIGHS;
                }
                counter++;
            } else {
                counter = 0;
                status = CLEAR;
            }
            if(counter == 3){
                switch(status){
                    case ZEROS:
                        self->event = ZERO_ACTIVITY;
                        break;
                    case HIGHS:
                        self->event = EARTHQUAKE;
                        break;
                    case VHIGHS:
                        self->event = CRITICAL_EARHQUAKE;
                        break;
                    default:
                        self->event = NOTHING;
                        break;
                }
                counter = 0;
                ssm_send_event(self);
                self->event = NOTHING;
            }
        }
        if(ESCAPE == getch())
            break;
    }
    printf("\nMonitoring over.");
}

void ssm_turn_on(seismometer_t *self){
    self->status = ON;
    self->event = SWITCHED_ON;
}

void ssm_turn_off(seismometer_t *self){
    self->status = OFF;
    self->event = SWITCHED_OFF;
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

//!*******************************************************************************************************************************
//!                                                     UNIT TESTS
//!*******************************************************************************************************************************


static void newSeismo_void_countZero(void **state){
    seismometer_t *self = ssm_new();
    assert_int_equal(self->count, 0);
    ssm_delete(self);
};//1

static void seismoAddListener_byName_indexZero(void**state){
    seismometer_t *self = ssm_new();
    listener_t *me = listener_new("Me");
    ssm_add_listener(self, me);
    assert_int_equal(ssm_get_listener_index(self, "Me"), 0);
    ssm_remove_listener(self, 0);
    listener_delete(me);
    ssm_delete(self);
};//2

static void newSeismo_deleteEmpty_False(void**state){
    seismometer_t *self = ssm_new();
    assert_false(ssm_remove_listener(self, 0));
    ssm_delete(self);
};//3

static void seismoAddTwoListeners_sameName_False(void**state){
    seismometer_t *self = ssm_new();
    listener_t *me1 = listener_new("Me");
    listener_t *me2 = listener_new("Me");
    ssm_add_listener(self, me2);
    assert_false(ssm_add_listener(self, me1));
    ssm_remove_listener(self, 0);
    listener_delete(me1);
    listener_delete(me2);
    ssm_delete(self);
};//4

static void seismoAddThreeListeners_deleteLast_countTwo(void**state){
    seismometer_t *self = ssm_new();
    listener_t *me1 = listener_new("Hello");
    listener_t *me2 = listener_new("earthquake");
    listener_t *me3 = listener_new("hide");
    ssm_add_listener(self, me1);
    ssm_add_listener(self, me2);
    ssm_add_listener(self, me3);
    ssm_remove_listener(self, 2);
    assert_int_equal(self->count, 2);
    ssm_remove_listener(self, 0);
    ssm_remove_listener(self, 0);
    listener_delete(me1);
    listener_delete(me2);
    listener_delete(me3);
    ssm_delete(self);
};//5

static void seismoAddListener_remove_removedName(void **state){
    seismometer_t *self = ssm_new();
    char *name = "Name";
    ssm_add_listener(self, listener_new(name));
    listener_t *me = ssm_remove_listener(self, 0);
    assert_string_equal(listener_get_name(me), name);
    listener_delete(me);
    ssm_delete(self);
};//6

static void newSeismo_switchOn_statusON(void**state){
    seismometer_t *self = ssm_new();
    ssm_turn_on(self);
    assert_int_equal(self->status, ON);
    ssm_delete(self);
};//7

static void seismoSwitchedOn_switchOff_eventOFF(void**state){
    seismometer_t *self = ssm_new();
    ssm_turn_on(self);
    ssm_turn_off(self);
    assert_int_equal(self->event, SWITCHED_OFF);
    ssm_delete(self);
};//8

int unit_test_run(void) {
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(newSeismo_void_countZero),
        cmocka_unit_test(seismoAddListener_byName_indexZero),
        cmocka_unit_test(newSeismo_deleteEmpty_False),
        cmocka_unit_test(seismoAddTwoListeners_sameName_False),
        cmocka_unit_test(seismoAddThreeListeners_deleteLast_countTwo),
        cmocka_unit_test(seismoAddListener_remove_removedName),
        cmocka_unit_test(newSeismo_switchOn_statusON),
        cmocka_unit_test(seismoSwitchedOn_switchOff_eventOFF)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
