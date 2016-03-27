#include<windows.h>

#include<stdio.h>

#include"threads.h"
//#include"thread.h"
#include"mutex.h"


void *readerFunc(void *args){
     shared_t * shared = (shared_t *)args;
     char *str = get_string(shared);
     while(1){
        shared_lock(shared);
        char a = get_symbol(shared);
        if(a == 'a' || a == 'A' || a == 'o' || a == 'O' || a == 'u'
            || a == 'U' || a == 'e' || a == 'E' || a == 'i' || a == 'I' || a == 'y' || a == 'Y')
            printf("%c; ", a);
        shared_unlock(shared);
        //Sleep(10 + strlen(str)/3);
     }
     return NULL;
}

thread_t *readerThread(shared_t *shared){
    return thread_create_args(readerFunc, shared);
}
