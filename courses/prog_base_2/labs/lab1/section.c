#include<stdlib.h>
#include<stdio.h>

#include"lab1.h"

struct section_s{
    int count;
    aud_t *auds[512];
};

aud_t *auditory_create(int number, int places, int *ERR);

section_t *section_new(int *ERR){
    *ERR = CORRECT;
    section_t *newSection = malloc(sizeof(struct section_s));
    if(!newSection){
        *ERR = MEMORY_LACK;
        return NULL;
    }
    newSection->count = 0;
    return newSection;
}

int section_isempty(section_t *psec, int *ERR){
    *ERR = CORRECT;
    if(!psec){
        *ERR = NULL_POINTER;
        return 0;
    }
    return psec->count == 0;
}

int section_count(section_t *psec, int *ERR){
    *ERR = CORRECT;
    if(!psec){
        *ERR = NULL_POINTER;
        return 0;
    }
    return psec->count;
}

void section_free(section_t *victim, int *ERR){
    *ERR = CORRECT;
    if(!victim){
        *ERR = NULL_POINTER;
        return;
    }
    int a;
    while(!section_isempty(victim, ERR)){
        a = auditory_saynumber(victim->auds[0], ERR);
        if(ERR)
            return;
        section_auditory_remove(victim, a, ERR);
    }
    free(victim);
}

void section_print_auditories(section_t *psec, int *ERR){
    *ERR = CORRECT;
    if(!psec){
        *ERR = NULL_POINTER;
        return;
    }
    int a;
    printf("\nAuditories:\n");
    for(int i = 0; i < psec->count; i++){
        a = auditory_saynumber(psec->auds[0], ERR);
        if(ERR){
            printf("CLOSED, ");
        }
        else{
            printf("%d, ", a);
        }
    }
    printf("\n");
}

int section_total_places(section_t *psec, int *ERR){
    *ERR = CORRECT;
    if(!psec){
        *ERR = NULL_POINTER;
        return 0;
    }
    int number = 0;
    int a;
    for(int i = 0; i < psec->count; i++){
        a = auditory_places(psec->auds[i], ERR);
        number += a;
    }
    *ERR = CORRECT;
    return number;
}

aud_t *section_auditory_add(section_t *psec, int number, int places, int *ERR){
    *ERR = CORRECT;
    if(!psec){
        *ERR = NULL_POINTER;
        return NULL;
    }
    if(section_auditory_find(psec, number, ERR)){
        *ERR = INCORRECT_NUMBER;
        return NULL;
    }
    if(psec->count +1 >= 512){
        *ERR = SECTION_OVERFLOW;
        return NULL;
    }
    aud_t *paud = auditory_create(number, places, ERR);
    if(*ERR)
        return NULL;
    psec->auds[psec->count] = paud;
    psec->count++;
    return paud;
}

void section_auditory_remove(section_t *psec, int number, int *ERR){
    *ERR = CORRECT;
    if(!psec){
        *ERR = NULL_POINTER;
        return;
    }
    if(section_isempty(psec, ERR)){
        *ERR = EMPTY_DELETION;
        return;
    }
    aud_t *toDelete = section_auditory_find(psec, number, ERR);
    if(!toDelete){
        *ERR = INCORRECT_NUMBER;
        return;
    }
    int i = 0;
    while(psec->auds[i] != toDelete)
        i++;
    free(toDelete);
    psec->count--;
    for(int j = i; j < psec->count; j++){
        psec->auds[j] = psec->auds[j+1];
    }
    psec->auds[psec->count] = NULL;
}

aud_t *section_auditory_find(section_t *psec, int number, int *ERR){
    *ERR = CORRECT;
    if(!psec){
        *ERR = NULL_POINTER;
        return 0;
    }
    for(int i = 0; i < psec->count; i++){
        if(number == auditory_saynumber(psec->auds[i], ERR))
            return psec->auds[i];
    }
    return NULL;
}
