/*-pedantic-errors --> warnings=errors*/
/*-std=c89 --> standart c89*/

#include<stdio.h>

void fillArray(int arr[10]);
void shiftArray(int arr[10]);
void printArray(int arr[10]);

int main(){
	int arr[10];
	fillArray(arr);
	shiftArray(arr); /*right,1*/
	printArray(arr);
	return 0;
}