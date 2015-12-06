#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<conio.h>

/*struct User{
	char username[30];
	char password[30];
	time_t birthdate;
	time_t regdate;
};

void printUser(struct User *p){
	printf("Username:\t %s\n", p->username);
	printf("Password:\t %s\n", p->password);
	printf("Birthdate:\t %s\n", ctime(&(p->regdate)));
	printf("Regdate:\t %s\n", ctime(&(p->regdate)));
}

int main(void){
	
	struct User *pUser= (struct User *)malloc(sizeof(struct User));
	struct tm *pTime= (struct tm *)malloc(sizeof(struct tm));
	
	strcpy(pUser->username, "Tiel_Lindemann");
	strcpy(pUser->password, "rammstein");
	
	pTime->tm_mday = 3;
	pTime->tm_mon = 0;
	pTime->tm_year = 63;
	pUser->birthdate = mktime(pTime);
	
	pTime->tm_mday = 9;
	pTime->tm_mon = 9;
	pTime->tm_year = 94;
	pUser->regdate = mktime(pTime);
	
	printf("%d\n", sizeof(struct User));
	
	printUser(pUser);
	
	FILE *pfile = fopen("test.bin", "wb");
	if(NULL == pfile){
		puts("oops!");
		return 0;
	}
	
	fwrite(pUser, sizeof(struct User), 1, pfile);
	
	fclose(pfile);
	
	getch();
	return 0;
}*/


int main(void){
	recur(0);
}