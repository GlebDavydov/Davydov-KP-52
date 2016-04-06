#include<stdio.h>

#include"lab1.h"


int error_output(int *ERR){
    switch(*ERR){
        case NULL_POINTER:
            printf("\nError: NULL pointer");
            return 1;
        case MEMORY_LACK:
            printf("\nError: impossible to allocate memory");
            return 1;
        case EMPTY_DELETION:
            printf("\nError: attempt to delete from empty section");
            return 1;
        case SECTION_OVERFLOW:
            printf("\nError: maximal auditory number reached");
            return 1;
        case INCORRECT_NUMBER:
            printf("\nError: invalid auditory number");
            return 1;
        case BAD_NAME:
            printf("\nError: empty name");
            return 1;
        case CORRECT:
        default:
            return 0;
    }
    return 0;
}

int main(void){
    my_test();
    int errcheck = 0;
    int *ERR = &errcheck;
    section_t *fourteen = section_new(ERR);
    if(error_output(ERR))
       return 0;
    section_auditory_add(fourteen, 67, 25, ERR);
    if(error_output(ERR))
       return 0;
    int plc = section_total_places(fourteen, ERR);
    if(error_output(ERR))
       return 0;
    printf("\nPlaces: %d", plc);
    auditory_occupy(fourteen, 67,  "Hadyniak", ERR);
    if(error_output(ERR))
       return 0;
    char *name = auditory_isoccupied(fourteen, 67, ERR);
    if(error_output(ERR))
       return 0;
    printf("Auditory 67-14 is occupied by %s", name);
    return 0;
}
