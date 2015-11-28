//variant N1

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>

void numberOutput(const char * string);

int main(){
	char string[100];
	fgets(string, 100, stdin);
	puts("\nString contains numbers: ");
	numberOutput(string);
	getch();
	return 0;
}

void numberOutput(const char *string){
	int counter = 0;
	for(int i = 0; string[i] != '\n' && string [i] != '\0'; i++){
		if(isdigit(string[i])){
			printf("%c, ", string[i]);
			counter++;
		}
	}
	printf("\nTotal contains %d numbers", counter);
}