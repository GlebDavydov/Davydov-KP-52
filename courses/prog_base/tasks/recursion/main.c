#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int calc(char* str){
	int a = 0;
	int b;
	if(isalpha(*str))
		a++;
	if(*(str+1) != '\n'){
		char *pstr = str+1;
		b = calc(pstr);
	}
	else
		return a;
	return a+b;
}

int main(){
	char string[160];
	fflush(stdin);
	fgets(string, 160, stdin);
	fclose(stdin);
	int res;
	res = calc(string);
	printf("%d", res);
	return 0;
}