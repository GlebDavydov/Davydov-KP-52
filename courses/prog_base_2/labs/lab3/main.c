#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "earthquake.h"

void calm(listener_t *self, callback_args args);
void panic(listener_t *self, callback_args args);

void hide(double n){
    Sleep(100);
} //damn good callback

void show(double n){
    Sleep(500);
    printf("\n%.2f", n);
}

int main(void){
    unit_test_run();
    srand(time(NULL));
    seismometer_t *lab = ssm_new("Explorer");
    ssm_add_listener(lab, listener_new("Michigan"), calm);
    ssm_add_listener(lab, listener_new("Yellowstone"), panic);
    ssm_add_listener(lab, listener_new("Carolina"), calm);
    ssm_add_listener(lab, listener_new("North Georgia"), panic);
    ssm_turn_on(lab);
    ssm_cycle(lab, show);
    ssm_turn_off(lab);
    ssm_delete(lab);
    return 0;
}
