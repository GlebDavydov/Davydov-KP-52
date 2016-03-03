#include"text.h"

int main(void){
	text_t *aText = text_new();
	sentence_create_beginning(aText, "I love coding in C");
	sentence_create_end(aText, "I love coding in Java, too.");
	sentence_t aSentence = sentence_create(aText, 1, "I hate calculus.");
	char *add = malloc(1024);
	sprintf(add, "the second sentence contained %d words", sentence_word_number(aSentence));
	sentence_create_end(aText, add);
	text_print(aText);
	sentence_delete(aText, 1);
	sentence_create(aText, 2, "the last sentence lies");
	text_print(aText);
	getch();
	text_free(aText);
	free(add);
}
