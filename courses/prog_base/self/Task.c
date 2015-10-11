#include <stdio.h>

int main(){
	int i=0;
	int n=103;
	int tens;
	int units;
	int hundreds;
	while(n<=987){
		hundreds =n/100;
		tens =(n-(hundreds*100))/10;
		units =n-(hundreds*100)-(tens*10);
		if((hundreds!=tens)&&(tens!=units)&&(hundreds!=units))
			i =i++;
		n =n++;
	}
	printf("%d", &i);
	return 0;
}