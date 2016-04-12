#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "main.h"

#define SPACEEND 0
#define AWORD 1
#define WORDDONE 2

// a sample exported function
int check(char *self, int n){
    int word_status = SPACEEND;
    int lw_counter;
    for(int i = n-1; i >= 0 && word_status != WORDDONE; i--){
        if(word_status == SPACEEND){
            if(self[i] != ' '){
                word_status = AWORD;
                lw_counter++;
            }
        } else if(word_status == AWORD){
            if(self[i] == ' ')
                word_status = WORDDONE;
            else
                lw_counter++;
        }
    }
    return lw_counter > 5;
}

void reaction(char *self, int n){
    char *p = (char *)malloc(sizeof(char) * n);
    char *res = (char *)malloc(sizeof(char) * n);
    strcpy(p, self);
    strtok(p, " ");
    res = p;
    while(p != NULL){
        p = strtok(NULL, " ");
        if(p != NULL)
            res = p;
    }
    printf("\nLast word: %s", res);
    free(p);
    free(res);
}

extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            // attach to process
            // return FALSE to fail DLL load
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
            break;
    }
    return TRUE; // succesful
}
