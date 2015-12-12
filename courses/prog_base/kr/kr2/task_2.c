#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct zachetka{
	char subj[30];
	int score;
	char mark;
} zlk;

typedef struct aStudent{
	char name[30];
	char surname[30];
	int number;
	time_t birthdate;
	*zlk zalikovka;
} student;

void initStructZlk(*zlk zlk1){
	zlk1->subj = "math and calculus";
	zlk1->score = 59;
	zlk1->mark = 'F';
}

void initStructStudent(*student stud1){
	stud1->name = "Ivan";
	stud1->surname = "Ivanov";
	stud1->math = malloc(sizeof(zlk));
	initStructZlk(stud1->zalikovka);
	struct tm *pTime = (struct tm *)malloc(sizeof(struct tm));
	pTime->tm_mday = 3;
	pTime->tm_mon = 0;
	pTime->tm_year = 98;
	stud1->birthdate = marktime(pTime);
}

*zlk dynInitZlk(*zlk zlk1){
	zlk1 = (*zlk)malloc(sizeof(zlk));
	return zlk1;
}

*stud dynInitStud(*student stud1){
	stud1 = (*student)malloc(sizeof(student));
	return stud1;
}

void abandonMemStud(*student stud1){
	free(stud1);
}

void abandonMemZlk(*zlk zlk1){
	free(zlk1);
}

void printStructZlk(*zlk zlk1){
	puts("zalikovka\n");
	printf("predmet: %s\nball: %d\otsinka: %c\n", zlk1->subj, zlk1->score, zlk1->mark);
}

void printStructStud(*student stud1){
	printf("im'ja: %s\nprizvshche: %s\nnomer: %d\n");
	printf("Birthdate:\t %s\n", ctime(&(stud1->birthdate));
	printStructZlk(stud->zalikovka);
}

void youthOutput(int size, *student stud[size]){
	time_t *pTime = malloc(sizeof(time_t));
	time(pTime);
	for(int i = 0; i < size; i++){
		if(pTime->tm_year - stud[i]->birthdate->tm_year < 18)
			printStructStud(stud[i]);
	}
}

void scoreBreakerOutput(int size, *student stud[size]){
	for(int i = 0; i < size; i++){
		if(stud[i]->score >= 75)
			printStructStud(stud[i]);
	}
}

*zlk userInitZlk(*zlk zlk1){
	printf("vvedit nazvu predmeta");
	char string[30];
	fflush(stdin);
	fgets(string, 30, stdin);
	fclose(stdin);
	stpcpy(zlk1->subj, string);
	printf("vvedit ball studenta");
	scanf("%d", &zlk1->score);
	if(score< 60)
		zlk1->mark = 'F';
	else if(score < 65)
		zlk1->mark = 'E';
	else if(score < 75)
		zlk1->mark = 'D';
	else if(score < 85)
		zlk1->mark = 'C';
	else if(score < 95)
		zlk1->mark = 'B';
	else zlk1->mark = 'A';
	
}