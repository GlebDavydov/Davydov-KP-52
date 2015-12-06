#include<stdio.h>
#include<math.h>
#include<time.h>
#include"array.c"

//any operation may be tested buy adding or deleting comment chars and changing function name to "equal"

void printArray(int arr[], int size);

int main(){
	int arr0[10];
	fillRand3(arr0, 10);
	printf("\nrandom fill:\n");
	printArray(arr0, 10); 
	
	int arr[10] = {1, 3, 5, 0, 4, 4, 5, 8, 6, 10};
	
	int testValue;
	testValue = maxOccurance(arr, 10);
	printf("\nMaxOccurance: %d \n", testValue);
	printArray(arr, 10);
	testValue = minValue(arr, 10);
	printf("\nminValue: %d \n", testValue);
	printArray(arr, 10);	
	testValue = minIndex(arr, 10); 
	printf("\nminIndex: %d \n", testValue);
	printArray(arr, 10);
	float testValue2 = meanValue(arr, 10);
	printf("\nmeanValue: %lf \n", testValue2);
	printArray(arr, 10);
	
	printf("\nmultiple array operations:\n");
	int arr1[10] = {1, 0, 0, 4, 5, 4, 7, 1, 1, 0};
	printArray(arr1, 10);
	int arr2[10] = {0, 1, 2, 3, 4, 5, 6, 1, 1, 1};
	puts("\n");
	printArray(arr2, 10);
	int res[10];
	land(arr1, arr2, res, 10);
	printf("\nLogical and:\n");
	printArray(res, 10);
	difference(arr1, arr2, res, 10);
	printf("\nDifference:\n");
	printArray(res, 10);
	mult(arr1, arr2, res, 10);
	printf("\nMultiplcation:\n");
	printArray(res, 10);
	printf("\nBoolean if array 1 is greater: %d", gt(arr1, arr2, 10));
	
	return 0;
}

void printArray(int arr[], int size){
	for(int i=0; i<size; i++){
		printf("%d, ", arr[i]);
	}
}