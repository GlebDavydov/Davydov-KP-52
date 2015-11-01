#include<stdio.h>
#include<math.h>
#include<time.h>
#include"array.c"

//any operation may be tested buy adding or deleting comment chars and changing function name to "equal"

void printArray(int arr[], int size);

int main(){
	/*int test[10];
	int* arr = &test[0]; //use for single array operations test
	fillRand(arr, 10);
	printArray(arr, 10); 
	*/	
	
	int test1[10] = {1, 0, 0, 4, 5, 4, 7, 1, 1, 0};
	int* arr1 = &test1[0];
	int test2[10] = {0, 1, 2, 3, 4, 5, 6, 1, 1, 1};			//use for multiple arrays operations test
	int* arr2 = &test2[0];
	int testresult[10];
	int* res = &testresult[0];
	
	land(arr1, arr2, res, 10); //land ~ mult
	
	/*int x;
	x = difference(arr1, arr2, res, 10); //difference ~ gt but without res
	printf("%d \n", x);*/
	printArray(res, 10);
	
	/* int testValue;
	testValue = maxOccurance(arr, 10); //maxOccurance ~ minValue, minIndex, meanIndex, float meanValue;
	printf("%d \n", testValue);
	printArray(arr, 10); */
	
	return 0;
}

void printArray(int arr[], int size){
	for(int i=0; i<size; i++){
		printf("%d, ", arr[i]);
	}
}