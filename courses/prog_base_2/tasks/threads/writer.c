#include<windows.h>

#include<string.h>

#include"threads.h"
//#include"thread.h"
#include"mutex.h"


void *writerFunc(void *args){
    shared_t * shared = (shared_t *)args;
    char *str = get_string(shared);
    int i = 0;
    while(1){
        shared_lock(shared);
        if(i < strlen(str)){
            change_symbol(shared, str[i]);
            i++;
        }
        else
            change_symbol(shared, '0');
        shared_unlock(shared);
        //Sleep(9 + (strlen(str)/3));
    }
    return NULL;
}

thread_t *writerThread(shared_t *shared){
    return thread_create_args(writerFunc, shared);
}
