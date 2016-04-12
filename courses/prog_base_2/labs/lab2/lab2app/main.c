#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>

#define ARRAY_SIZE 100
#define SPACE_CHANCE 10

#include "array.h"

typedef int (*chk_f)(char *self, int n);
typedef void (*react_f)(char * self, int b);

typedef struct dynamic_s {
    HANDLE hLib;
    chk_f chk;
    react_f react;
} dynamic_t;

dynamic_t * dynamic_init(const char * dllName);

void dynamic_clean(dynamic_t * dyn);
char *choose_way(void);

int main(void){
    char *dllName = choose_way();
    dynamic_t *dll = dynamic_init(dllName);
    if(!dll){
        printf("\nError: could not recieve dll name");
        return 0;
    }
    if(!dll->chk || !dll->react){
        printf("\nError: could not recieve dll funcltion name");
        return 0;
    }

    char sample[ARRAY_SIZE];
    srand(time(NULL));
    printf("\n");
    for(int i = 0; i < ARRAY_SIZE; i++){
        switch(rand() % SPACE_CHANCE + 1){
            case SPACE_CHANCE:
                add_elem(sample, i, ' ');
                break;
            default:
                add_elem(sample, i, rand() % 58 + 65);
                break;
        }
    }
    printf("\n%s", sample);
    if(dll->chk(sample, ARRAY_SIZE)){
        printf("\nReaction positive!");
        dll->react(sample, ARRAY_SIZE);
    }
    else
        printf("\nReaction negative!");
    dynamic_clean(dll);
    return 0;
}

char *choose_way(void){
    printf("\nENTER USED DYNAMIC LIBRARY NUMBER (1, 2)\n");
    int a;
    while(1){
        a = getchar();
        switch(a){
            case '1':
                printf("\nLIBARY 1 CHOSEN");
                return "lab2dynamic1.dll";
            case '2':
                printf("\nLIBARY 2 CHOSEN");
                return "lab2dynamic2.dll";
            default:
                printf("\nINCORRECT, TRY AGAIN\n");
        }
    }
}

dynamic_t * dynamic_init(const char * dllName) {
    dynamic_t * dyn = malloc(sizeof(struct dynamic_s));
    dyn->hLib = LoadLibrary(dllName);
    dyn->chk = NULL;
    dyn->react = NULL;
    if (NULL != dyn->hLib) {
        dyn->chk = (chk_f)GetProcAddress(dyn->hLib, "check");
        dyn->react = (react_f)GetProcAddress(dyn->hLib, "reaction");
        return dyn;
    } else {
        return NULL;
    }
}

void dynamic_clean(dynamic_t * dyn) {
    FreeLibrary(dyn->hLib);
    free(dyn);
}
