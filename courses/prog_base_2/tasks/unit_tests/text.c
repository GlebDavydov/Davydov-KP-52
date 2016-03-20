#include"text.h"

#define A_WORD 1
#define NO_WORD 0

struct text_s {
    int count;
	sentence_t  st[1024];
};

int text_count(text_t *ptext, int *ERR){
    if(!ptext){
        *ERR = NULL_POINTER;
        return 0;
    }
    return ptext->count;
}

text_t *text_new(int *ERR){
    *ERR = CORRECT;
	text_t *newText = malloc(sizeof(text_t));
	if(!newText){
		*ERR = MEMORY_LACK;
		return NULL;
    }
    newText->count = 0;
	return newText;
}

int text_isempty(text_t *ptext, int *ERR){
    *ERR = CORRECT;
	if(ptext == NULL){
		*ERR = NULL_POINTER;
		return 0;
    }
	return ptext->count == 0;
}

void text_free(text_t *victim){
	free(victim);
}

int text_word_number(text_t *ptext, int *ERR){
    *ERR = CORRECT;
	if(ptext == NULL){
		*ERR = NULL_POINTER;
		return 0;
    }
    int num = 0;
    for(int i = 0; i < ptext->count; i++){
        num += sentence_word_number(ptext->st[i], ERR);
        if(*ERR)
            return 0;
    }
    return num;
}

void text_print(text_t *ptext, int *ERR){
    *ERR = CORRECT;
	if(ptext == NULL){
		*ERR = NULL_POINTER;
		return;
    }
	for(int i = 0; i < ptext->count; i++)
        printf(ptext->st[i]);
	printf("\n");
}

char *sentence_dot(char *string, int *ERR){
    *ERR = CORRECT;
	if(string == NULL){
		*ERR = NULL_POINTER;
		return NULL;
    }
	if(string[strlen(string) - 1] != '.'){
		char *new_string = malloc(strlen(string) + 1);
		if(new_string == NULL){
            *ERR = MEMORY_LACK;
            return NULL;
		}
		sprintf(new_string, "%s.", string);
		return(new_string);
	}
	return string;
}

sentence_t sentence_create_beginning(text_t *ptext, char *sent_cont, int *ERR){
    *ERR = CORRECT;
	if(ptext == NULL){
        *ERR = NULL_POINTER;
        return NULL;
	}
	if(ptext->count >= 1024){
        *ERR = TEXT_OVERFLOW;
        return NULL;
	}
	sent_cont = sentence_dot(sent_cont, ERR);
	if(*ERR)
        return NULL;
    for(int i = ptext->count; i > 0; i--)
        ptext->st[i] = ptext->st[i - 1];
    ptext->st[0] = sent_cont;
    ptext->count++;
	return ptext->st[0];
}

sentence_t sentence_create_end(text_t *ptext, char *sent_cont, int *ERR){
    *ERR = CORRECT;if(ptext == NULL){
        *ERR = NULL_POINTER;
        return NULL;
	}
	if(ptext->count >= 1024){
        *ERR = TEXT_OVERFLOW;
        return NULL;
	}
	sent_cont = sentence_dot(sent_cont, ERR);
	if(*ERR)
        return NULL;
	ptext->st[ptext->count] = sent_cont;
    ptext->count++;
	return ptext->st[ptext->count - 1];
}

sentence_t sentence_create(text_t *ptext, int index, char *sent_cont, int *ERR){
    *ERR = CORRECT;
	if(ptext == NULL){
        *ERR = NULL_POINTER;
        return NULL;
	}
	if(ptext->count >= 1024){
        *ERR = TEXT_OVERFLOW;
        return NULL;
	}
	sent_cont = sentence_dot(sent_cont, ERR);
	if(*ERR)
        return NULL;
	if(index < 0)
		index = -index;
	if(index > ptext->count){
        *ERR = INCORRECT_INDEX;
        return NULL;
	}
	if(index == ptext->count)
		return sentence_create_end(ptext, sent_cont, ERR);
	if(index == 0)
        return sentence_create_beginning(ptext, sent_cont, ERR);
    for(int i = ptext->count; i > index; i--)
        ptext->st[i] = ptext->st[i - 1];
    ptext->st[index] = sent_cont;
    ptext->count++;
	return ptext->st[index];
}

void sentence_delete_beginning(text_t *ptext, int *ERR){
	*ERR = CORRECT;
	if(ptext == NULL){
        *ERR = NULL_POINTER;
        return;
	}
	if(text_isempty(ptext, ERR)){
        *ERR = EMPTY_DELETION;
        return;
	}
	for(int i = 0; i < ptext->count; i++)
        ptext->st[i] = ptext->st[i + 1];
    ptext->st[ptext->count - 1] = NULL;
    ptext->count--;
}

void sentence_delete_end(text_t *ptext, int *ERR){
	*ERR = CORRECT;
	if(ptext == NULL){
        *ERR = NULL_POINTER;
        return;
	}
	if(text_isempty(ptext, ERR)){
        *ERR = EMPTY_DELETION;
        return;
	}
    ptext->st[ptext->count - 1] = NULL;
    ptext->count--;
}

void sentence_delete(text_t *ptext, int index, int *ERR){
	*ERR = CORRECT;
	if(ptext == NULL){
        *ERR = NULL_POINTER;
        return;
	}
	if(text_isempty(ptext, ERR)){
        *ERR = EMPTY_DELETION;
        return;
	}
	if(index < 0)
		index = -index;
	if(index > ptext->count){
        *ERR = INCORRECT_INDEX;
        return;
	}
    if(index == ptext->count){
		sentence_delete_end(ptext, ERR);
		return;
	}
	if(index == 0){
		sentence_delete_beginning(ptext, ERR);
		return;
	}
	for(int i = index; i < ptext->count; i++)
        ptext->st[i] = ptext->st[i + 1];
    ptext->st[ptext->count - 1] = NULL;
    ptext->count--;
}

int sentence_word_number(sentence_t curr_sentence, int *ERR){ //ÃŒ∆≈“ œ–»√Œƒ»»“‹—ﬂ!!!
	*ERR = CORRECT;
	if(!curr_sentence){
        *ERR = NULL_POINTER;
        return 0;
	}
	int state = NO_WORD;
	int number = 0;
	for(int i = 0; i < strlen(curr_sentence); i++){
		if(state == NO_WORD){
			if(isalpha(curr_sentence[i])){
				state = A_WORD;
				number++;
			}
		}
		if(state == A_WORD){
			if(!isalpha(curr_sentence[i]))
				state = NO_WORD;
		}
	}
	return number;
}

void sentence_print(sentence_t curr){
	printf("%s", curr);
}
