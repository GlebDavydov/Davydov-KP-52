#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>

struct Student{
	int number;
	char name[30];
	int score;
};

void printelem(int size, struct Student gr[size], int index){
	int otstup = 32 - (strlen(gr[index].name));
	printf("%d.%s", gr[index].number, gr[index].name);
	for(int i = 1; i <= otstup; i++){
		printf(" ");
	}
	if(index < 9)
		printf(" ");
	printf("%d\n", gr[index].score);
}

void printstruct(int size, struct Student gr[size]){
	printf("\n");
	for(int i = 0; i < size; i++){
		printelem(size, gr, i);
	}
}

int lessThen30(int size, struct Student gr[size]){
	int pres;
	pres = 0;
	for(int i = 0; i < size; i++){
		if(gr[i].score < 30)
			pres++;
	}
	return pres;
}

int changelem(int size, struct Student gr[size], int index){
	printf("Input new name\n");
	fflush(stdin);
	gets(gr[index].name);
	fclose(stdin);
}

int main(){
	struct Student group[20] = {{1, "Adams Eric", 99}, {2, "Android", 100} , {3, "Atilla", 25}, {4, "Ceasar Gaius Julius", 101}, {5, "Davydov Glib", 43},
	{6, "Dickinson Bruce", 45}, {7, "Error: student not found", 404}, {8, "Faramir of Gondor", 56}, {9, "Hetfield James", 29}, {10, "Heretic! Mutant!", 0}, 
	{11, "Ivanov Ivan", 30}, {12, "Krysiuk Andriy", 50}, {13, "Kenny", 30}, {14, "Lindemann Tiel", 40}, {15, "Mustaine David", 99}, 
	{16, "Neo", 65535}, {17, "Salenko Anton", 100}, {18, "Sharovarsky Konstantine", 100}, {19, "Urukov Dmitro", 101}, {20, "Zerg Rush", 6}};
	printstruct(20, group);
	int res = lessThen30(20, group);
	printf("H\\A y %d\n", res);
	int index = 0;
	printf("input number\n");
	scanf("%d", &index);
	while(index < 1 || index > 20){
		printf("Incorrect. Try again\n");
		scanf("%d", &index);
	}
	index--;
	changelem(20, group, index);
	puts("\n");
	printelem(20, group, index);
	return 0;
}