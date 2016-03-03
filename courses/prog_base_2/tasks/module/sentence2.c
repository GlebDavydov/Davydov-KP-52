#include"text.h"

#define A_WORD 1
#define NO_WORD 0

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
