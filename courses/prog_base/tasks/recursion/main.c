#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int calc(char* str){
	int a = 0;
	if(isalpha(*str))
		a++;
	if(*(str+1) != '\0')
		return a+calc(str+1);
	else
		return a;
}

int main(){
	char string[160];
	puts("input any string");
	fflush(stdin);
	fgets(string, 160, stdin);
	fclose(stdin);
	int res;
	res = calc(string) > 5;
	printf("%d", res);
	return 0;
}