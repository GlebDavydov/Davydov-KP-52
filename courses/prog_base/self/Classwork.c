#include<stdio.h>
#include<stdlib.h>
#include<time.h>
/*
void fillSandclock(int n, int arr[n][n]){
	int k = 1;
	for(int i=0; i < n; i++){
		int j=0;
		for(j=0; j<n; j++){
			arr[i][j] = 0;
		}
		for(j == fmin(i, n-i); j == fmax(i, n-i); j++, k++)
			arr[i][j] = k;
	}
}
*/
void printMatrix(int n, int arr[n][n]){
	for(int k=0; k < n*n; k++){
		if(k%n == 0)
			puts("\n");
		printf("%5d", arr[k/n][k%n]);
	}
}
/*
int main(void){
	puts("Input matrix size: ");
	int n;
	scanf("%d", &n);
	int matrix[n][n];
	int *arr = &matrix[0][0];
	fillSandclock(n, arr);
	printMatrix(n, arr);
	return EXIT_SUCCESS;
}*/

void fillRand(int size, int arr[size][size]){
	srand(time(NULL));
	for(int i = 0; i < size*size; i++)
		arr[i/size][i%size] = rand()%(100+1);
}

void flipCCW90(int size, int arr[size][size], a, b){
	int distance;
	int up;
	for(int i = a; i >= 0; i--)
		up++;
	int down;
	for(int i = a; i < size; i++)
		down++;
	distance = fmin(up, down);
	int left;
	for(int i = b; i >= 0; i--)
		left++;
	distance = fmin(distance, left);
	int right;
	for(int i = b; i < size; i++)
		right++;
	distance = fmin(distance, right);
	
}

int main(void){
	int n;
	puts("Input matrix size: ");
	scanf("%d", &n);
	int matrix[n][n];
	int *arr = &matrix[0][0];
	fillRand(n, arr);
	printMatrix(n, arr);
	puts("\n Input element index: ");
	int a, b;
	scanf("%d %d", &a, &b);
	flipCCW90(n, arr, a, b);
	printMatrix(n, arr);
	return EXIT_SUCCESS;
}