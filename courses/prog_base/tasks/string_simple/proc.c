#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int maxIndex(int arr[], int size);

char * process(char *resultStr, const char *textLines, int linesNum, const char *extraStr){
	int wordAmount[linesNum];
	int i;
	char *tl;
	const char findit =' ';
	char *find = &findit;
	for(i=0; i < linesNum; i++){
		char temporary[100];
		char *temp = &temporary[0];
		wordAmount[i]=0;
		strcpy(tl, &textLines[i]);
		while(temp!=NULL){
			char *temp = strstr(tl, find);
			wordAmount[i]++;
		}
	}
	int *wA = &wordAmount[0];
	int x = maxIndex(wA, linesNum);
	if(wordAmount[x]==0){
		sprintf(resultStr, "0 NULL", extraStr); 
		return resultStr;
	}
    char *p;
    char *str;
	sprintf(str, "", textLines[x]);
    char del[] = " ";
    p = strtok(str, del);
    while(p != NULL){
		sprintf(resultStr, "", resultStr, p);
        p = strtok(NULL, del);
    }
	sprintf(resultStr, "%d ", wordAmount[x], resultStr);
	return resultStr;
}

int maxIndex(int arr[], int size){
	int j=0;
	int maxArr=arr[0];
	int i=1;
	for(i=1; i < size; i++){
		if(arr[i] > maxArr){
			maxArr = arr[i];
			j=i;
		}
	}
	return j;
}