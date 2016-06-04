#include <stdio.h>
#include <stdlib.h>

#include "database.h"
#include "server.h"


int err_proc(int *err){
    if(*err){
        if(*err == INVALID_REQUEST){
            printf("\nError: invalid request.");
        } else if(*err == STEP_ERROR){
            printf("\nStep error.");
        } else if(*err == PROCESS_FAILURE){
            printf("\nProcess failed.");
        }
        return(1);
    }
    return 0;
}

int main(void){
    list_t *list1 = list_new();
    http_request_startServer(list1);
    list_free(list1);
    return 0;
}
