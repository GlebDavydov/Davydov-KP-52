#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "earthquake.h"

void hide(double n){
    Sleep(100);
} //damn good callback

void show(double n){
    Sleep(500);
    printf("\n%.2f", n);
}

int main(void){
    //unit_test_run();
    srand(time(NULL));
    seismometer_t *lab = ssm_new();
    ssm_add_listener(lab, listener_new("Michigan"));
    ssm_add_listener(lab, listener_new("Yellowstone"));
    ssm_add_listener(lab, listener_new("Carolina"));
    ssm_add_listener(lab, listener_new("North Georgia"));
    ssm_turn_on(lab);
    ssm_send_event(lab);
    ssm_cycle(lab, show);
    ssm_turn_off(lab);
    ssm_send_event(lab);
    while(ssm_get_count(lab)){
        listener_delete(ssm_remove_listener(lab, 0));
    }
    ssm_delete(lab);
}
