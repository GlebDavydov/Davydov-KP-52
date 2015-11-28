#include<stdio.h>
#include<stdlib.h>
#include"automata.c"

void printArray(int arr[], int size);

void main(){
	int res[10];
	int moves[10] = {3, 12, 5, 102, 102, 102, 5, 12, 3, 12};
	printArray()
	int *input = &moves[0];
	int *result = &res[0];
	int x = run(input, 10, result, 10);
	printf("%d \n", x);
	printArray(result, 10);
}

printArray(int arr[], int size){
	for(int i=0; i<size; i++)
		printf("%d ", arr[i]);
}