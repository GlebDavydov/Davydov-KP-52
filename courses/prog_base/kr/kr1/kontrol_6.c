#include<stdio.h>
#include<stdlib.h>

//Davydov KP-52 Variant 17
int size;

void printMatr(int arr[][size], int size);
void fillMatrSimple(int arr[][size], int size);
int sumDiagEdge(int arr[][size], int size);

void main(){
	scanf("%d", size);
	int matr[size][size];
	int* arr = &matr[0][0]; 
	fillMatrSimple(arr, size);
	printMatr(arr, size);
	int x;
	x = sumDiagEdge(arr, size);
	printf("%d", &x);
}

void printMatr(int mat[][size], int size){
    int i, j;
    int n = size;
    printf("{ ");
    for (i = 0; i < size; i++) {
        printf("{");
        for (j = 0; j < size; j++) {
            printf("%5i, ", mat[i][j]);
        }
        printf("}");
        if ( i < n - 1)
            printf("\n  ");
    }
    printf(" };\n");
}

void fillMatrSimple(int arr[][size], int size){
	int num=1;
	for(int i=0; i<size; i++){
		for(int j = 0; j<size; i++){
			arr[i][j]=num;
			num++;
		}
	}
}

int sumDiagEdge(int arr[][size], int size){
	int x=0;
	for(int i = 0; i<size; i++){
		for(int j = 0; j < size; j++){
			if((i==j)||(i==0)||(i==size)||(j==0)||(j==size))
			x += arr[i][j];
		}
	}
	return x;
}