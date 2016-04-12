#include <stdlib.h>
#include <string.h>

#include "array.h"

int add_elem(char *self, int index, char elem){
    if(self == NULL || index < 0)
        return 0;
    self[index] = elem;
    return 1;
}

char get_elem(char *self, int index){
    if(self == NULL || index < 0)
        return 0;
    return self[index];
}

int delete_elem(char *self, int index){
    if(self == NULL || index < 0)
        return 0;
    self[index] = 0;
    return 1;
}
