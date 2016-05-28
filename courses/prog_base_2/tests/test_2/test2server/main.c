#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "server.h"

int main(void){
    list_t *teachers = list_new();
    http_request_startServer(teachers);
    list_free(teachers);
    return 0;
}
