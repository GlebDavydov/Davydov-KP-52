#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
	char *p;
	p = malloc(400);
	fgets(p, 400, stdin);
	char *tmp = malloc(1);
	char *smb = malloc(1);
	for(tmp = p, smb = p; *tmp != '\n'; tmp++){
		if(*tmp > *smb)
			smb = tmp;
	}
	char *res = malloc(50);
	sprintf(res, "the highest index is %d (symbol %c)", *smb, *smb);
	puts(res);
	free(res);
	free(smb);
	free(tmp);
	free(p);
	return 0;
}