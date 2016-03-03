#include"text.h"

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
