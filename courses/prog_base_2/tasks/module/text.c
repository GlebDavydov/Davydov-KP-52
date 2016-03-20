#include"text.h"

#define A_WORD 1
#define NO_WORD 0

struct text_s {
    int count;
	sentence_t  st[1024];
};

text_t *text_new(void){
	text_t *newText = malloc(sizeof(text_t));
	if(!newText)
		EXIT_FAILURE;
    newText->count = 0;
	return newText;
}

int text_isempty(text_t *ptext){
	if(ptext == NULL)
		EXIT_FAILURE;
	return ptext->count == 0;
}

void text_free(text_t *victim){
	free(victim);
}

int text_word_number(text_t *ptext){
	if(ptext == NULL)
		EXIT_FAILURE;
    int num = 0;
    for(int i = 0; i < ptext->count; i++)
        num += sentence_word_number(ptext->st[i]);
    return num;
}

void text_print(text_t *ptext){
	if(ptext == NULL)
		EXIT_FAILURE;
	for(int i = 0; i < ptext->count; i++)
        printf(ptext->st[i]);
	printf("\n");
}

char *sentence_dot(char *string){
	if(string == NULL)
		//return ERROR_MESSAGE;
		EXIT_FAILURE;
	if(string[strlen(string) - 1] != '.'){
		char *new_string = malloc(strlen(string) + 1);
		if(new_string == NULL)
			//return ERROR_MESSAGE;
			EXIT_FAILURE;
		sprintf(new_string, "%s.", string);
		return(new_string);
	}
	return string;
}

sentence_t sentence_create_beginning(text_t *ptext, char *sent_cont){
	if(ptext == NULL || ptext->count >= 1024)
		EXIT_FAILURE;
	sent_cont = sentence_dot(sent_cont);
    for(int i = ptext->count; i > 0; i--)
        ptext->st[i] = ptext->st[i - 1];
    ptext->st[0] = sent_cont;
    ptext->count++;
	return ptext->st[0];
}

sentence_t sentence_create_end(text_t *ptext, char *sent_cont){
	if(ptext == NULL || ptext->count >= 1024)
		EXIT_FAILURE;
	sent_cont = sentence_dot(sent_cont);
	ptext->st[ptext->count] = sent_cont;
    ptext->count++;
	return ptext->st[ptext->count - 1];
}

sentence_t sentence_create(text_t *ptext, int index, char *sent_cont){
	if(ptext == NULL)
		EXIT_FAILURE;
	sent_cont = sentence_dot(sent_cont);
	//if(sent_cont == ERROR_MESSAGE)
		//return ERROR_MESSAGE;
	if(index < 0)
		index = -index;
	if(index > ptext->count)
		//return ERROR_MESSAGE;
		EXIT_FAILURE;
	if(index == ptext->count)
		return sentence_create_end(ptext, sent_cont);
	if(index == 0)
        return sentence_create_beginning(ptext, sent_cont);
    for(int i = ptext->count; i > index; i--)
        ptext->st[i] = ptext->st[i - 1];
    ptext->st[index] = sent_cont;
    ptext->count++;
	return ptext->st[index];
}

void sentence_delete_beginning(text_t *ptext){
	if(ptext == NULL)
		EXIT_FAILURE;
	if(text_isempty(ptext))
		EXIT_FAILURE;
	for(int i = 0; i < ptext->count; i++)
        ptext->st[i] = ptext->st[i + 1];
    ptext->st[ptext->count - 1] = NULL;
    ptext->count--;
}

void sentence_delete_end(text_t *ptext){
	if(ptext == NULL)
		EXIT_FAILURE;
	if(text_isempty(ptext))
		EXIT_FAILURE;
    ptext->st[ptext->count - 1] = NULL;
    ptext->count--;
}

void sentence_delete(text_t *ptext, int index){
	if(ptext == NULL)
		EXIT_FAILURE;
	if(index < 0)
		index = -index;
	if(index > ptext->count)
		EXIT_FAILURE;
	if(index == ptext->count){
		sentence_delete_end(ptext);
		return;
	}
	if(index == 0){
		sentence_delete_beginning(ptext);
		return;
	}
	for(int i = index; i < ptext->count; i++)
        ptext->st[i] = ptext->st[i + 1];
    ptext->st[ptext->count - 1] = NULL;
    ptext->count--;
}

int sentence_word_number(sentence_t curr_sentence){
	if(!curr_sentence)
		//return ERROR_MESSAGE;
		EXIT_FAILURE;
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
