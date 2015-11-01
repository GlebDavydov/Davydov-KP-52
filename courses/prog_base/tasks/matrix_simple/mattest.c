#include <stdlib.h>
#include <stdio.h>
#include <time.h>
void printMatrix(int mat[4][4]);

int main(){
	srand(time(NULL));
	int mat1[4][4];
	fillRand(mat1);
	printMatrix(mat1);
	puts(" ");
	rotateCW270(mat1);
	printMatrix(mat1);
	puts(" ");
	flipH(mat1);
	printMatrix(mat1);
	puts(" ");
	transposMain(mat1);
	printMatrix(mat1);
	return 0;
}

void printMatrix(int mat[4][4]){
    int i, j;
    int n = 4;
    printf("{ ");
    for (i = 0; i < n; i++) {
        printf("{");
        for (j = 0; j < n; j++) {
            printf("%5i, ", mat[i][j]);
        }
        printf("}");
        if ( i < n - 1)
            printf("\n  ");
    }
    printf(" };\n");
}