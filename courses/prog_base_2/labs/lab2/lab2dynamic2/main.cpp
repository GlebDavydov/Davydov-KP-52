#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "main.h"

int check(char *self, int n){
    char *p = (char *)malloc(sizeof(char) * n);
    strcpy(p, self);
    int counter;
    strtok(p, " ");
    while(p != NULL){
        counter++;
        p = strtok(NULL, " ");
    }
    free(p);
    return counter > 5;
}

void reaction(char *self, int n){
    char *p = (char *)malloc(sizeof(char) * n);
    strcpy(p, self);
    int c = 0;
    strtok(p, " ");
    while(p != NULL){
        printf("\nWord %d: %s;", ++c, p);
        p = strtok(NULL, " ");
    }
    free(p);
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
