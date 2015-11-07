#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int run(int moves[], int movesLen, int res[], int resLen){
	//alphabet = 3, 5, 12, 102;
	enum operations{blank=99, terminal, repeat, pop};
		for(int j=0; j < resLen; j++){
		res[j] = 0;
	}
	int machine[4][4] = {1, 1000 + pop, 1000 + 5, terminal, 					
					terminal, 2000 + 21, 2000 + blank, 3000 + 625,
					terminal, terminal, 3000 + repeat, 3000 + pop,
					2000 + 25, 1000 + 6, 7, 3000 + 627};				//new state is machine[state][k]/1000, operation is machine[state][k]%1000
	int state;
	int input;
	int k;
	int j;
	int i;
	for(state=0, j=0, i=0; i < movesLen; i++){
		switch(moves[i]){
			case 3:
				k = 0;
				break;
			case 5:
				k = 1;
				break;
			case 12:
				k = 2;
				break;
			case 102:
				k = 3;
				break;
			default:
				return j;
		}
		switch (machine[state][k]%1000){
			case terminal:
				return j;
			case pop:
				if(j==0)
					return j;
				res[j] = 0;
				j--;
				state = machine[state][k]/1000;
				break;
			case blank:
				state = machine[state][k]/1000;
				break;
			case repeat:
				i--;
				state = machine[state][k]/1000;
				break;
			default:
				if(j==resLen)
					return j;
				res[j] = machine[state][k]%1000;
				state = machine[state][k]/1000;
				j++;
				break;
		}
	}
	return j;
}