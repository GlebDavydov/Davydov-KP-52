#include<stdlib.h>

#include"lab1.h"

struct aud_s{
    int number;
    int places;
    char *occupier;
};

aud_t *auditory_create(int num, int plcs, int *ERR){
    aud_t *newAud = malloc(sizeof(struct aud_s));
    if(!newAud){
        *ERR = MEMORY_LACK;
        return NULL;
    }
    newAud->number = num;
    if(plcs <= 0 || plcs > 500)
        plcs = 50;
    newAud->places = plcs;
    return newAud;
}

int auditory_saynumber(aud_t *paud, int *ERR){
    if(!paud){
        *ERR = NULL_POINTER;
        return 0;
    }
    return paud->number;
}
int auditory_places(aud_t *paud, int *ERR){
    if(!paud){
        *ERR = NULL_POINTER;
        return 0;
    }
    return paud->places;
}
int auditory_occupy(section_t *psec, int number, char *sname, int *ERR){
    if(!psec){
        *ERR = NULL_POINTER;
        return 0;
    }
    if(!sname){
        *ERR = BAD_NAME;
        return 0;
    }
    aud_t *paud = section_auditory_find(psec, number, ERR);
    if(!paud){
        *ERR = INCORRECT_NUMBER;
        return 0;
    }
    if(paud->occupier){
        return 0;
    }
    paud->occupier = sname;
    return 1;
}
int auditory_deoccupy(section_t *psec, int number, int *ERR){
    if(!psec){
        *ERR = NULL_POINTER;
        return 0;
    }
    aud_t *paud = section_auditory_find(psec, number, ERR);
    if(!paud){
        *ERR = INCORRECT_NUMBER;
        return 0;
    }
    if(!paud->occupier)
        return 0;
    paud->occupier = NULL;
    return 1;
}

char *auditory_isoccupied(section_t *psec, int number, int *ERR){
    if(!psec){
        *ERR = NULL_POINTER;
        return 0;
    }
    aud_t *paud = section_auditory_find(psec, number, ERR);
    if(!paud){
        *ERR = INCORRECT_NUMBER;
        return 0;
    }
    return paud->occupier;
}
