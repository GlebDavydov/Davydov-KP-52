#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void main(){
	struct sdk_num{
		int num;
		int orzero;
	};
	struct sdk_num sdk[9][9] = {0};
	int status = 0;
	srand(time(NULL));
	for(int i = 1; i <= 9; i++){													//числа, которыми заполняется массив
		int a;
		for(int j = 0; j < 8; j++){													//номера строк массива
			a = rand()%(9+0);														//случайный номер ячейки в стоке массива
			do {
				a = a++ % 9;													
				for(int k = 0; k < 9; k++){
					if(sdk[j][a].num != 0){
						status = 1;
						break;
					}
					if(sdk[j][k].num == i){
						status = 1;
						break;
					}
					if(sdk[k][a].num == i){
						status = 1;
						break;
					}
					status = 0;
				}
				for(int k = 0; k < 9; k++){
						if(sdk[ 3 * (a / 3) + (k / 3) ][ 3 * ( j / 3 ) + (k % 3) ].num == i){
						status = 1;
						break;
						}
						status = 0;
				}
				printf("status: %d, row: %d, column: %d, number: %d \n", status, j, a, i);
			}
			while(status != 0);
			sdk[j][a].num = i;
		}
	}
	for(int k=0; k < 81; k++){
		if(k%9 == 0)
			puts("\n");
		printf("%5d", sdk[k/9][k%9].num);
	}
	/*int lvl;
	printf("input difficulcy level (1, 2 or 3): ")
	scanf("&d", &lvl);*/
}