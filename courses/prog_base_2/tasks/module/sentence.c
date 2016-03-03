#include"text.h"

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
