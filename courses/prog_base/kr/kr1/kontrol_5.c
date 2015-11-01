#include<stdio.h>
#include<stdlib.h>

//Davydov KP-52 Variant 17

void printArray(int arr[], int size);
void scanArray(int arr[], int size);
int minValue(int arr[], int size);
void sum(int arr1[], int arr2[], int res[], int size);

void main(){
	int size;
	puts("input array size");
	scanf("%d", &size);
	int test1[size];
	int* arr1 = &test1[0];
	puts("input first array elements");
	scanArray(arr1, size);
	int test2[size];
	int* arr2 = &test2[0];
	puts("input second array elements");
	scanArray(arr2, size);
	int testresult[size];
	int* res = &testresult[0];
	sum(arr1, arr2, res, size);
	printf("Sum  ");
	printArray(res, size);
	int x;
	x = minValue(res, size);
	printf("Minimal value is  %d", x);
}

void printArray(int arr[], int size){
	for(int i=0; i<size; i++){
		printf("%d, ", arr[i]);
	}
}

void scanArray(int arr[], int size){
	for(int i=0; i < size; i++){
		int ch;
		scanf("%d", &ch);
		arr[i] = ch;
	}
}

int minValue(int arr[], int size){
	int minElem = arr[0];
	for(int i = 0; i < size; i++){
		if(arr[i] < minElem)
			minElem = arr[i];
	}
	return minElem;
}

void sum(int arr1[], int arr2[], int res[], int size){
	for(int i=0; i < size; i++){
		res[i] = arr1[i] + arr2[i];
	}
}