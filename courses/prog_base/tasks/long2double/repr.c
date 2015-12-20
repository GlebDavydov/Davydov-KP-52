#include<stdio.h>
#include<math.h>

double long2double(long long int);

int main(){
	long long int a;
	printf("Input an integer\n");
	scanf("%lld", &a);
	double b;
	b = long2double(a);
	printf("%.325lf", b);
	return 0;
}

double long2double(long long int a){
	int i;
	double a1;
	unsigned int bit[64];
	unsigned int counter=0;
	const unsigned int mask = 1 << 31;
	for(i=1; i<=64; i++){
		bit[counter]=(mask & a ? '1' : '0');
	counter++;
	}
	double s;
	if(bit[0]==1)
		s=-1;
	else
		s=1;
	double exponent=0;
	for(counter=1; counter<=11; counter++){
		if(bit[counter]==1)
			exponent += pow(2, 11-counter);
	}
	double fraction=0;
	for(counter=12; counter<=63; counter++){
		if(bit[counter]==1)
			fraction += pow(2, 11-counter);
	}
	if(exponent==2047){
		if(fraction==0){
			if(s=1)
				return +INFINITY;
			else
				return -INFINITY;
		}
		else {
			if(s=1)
				return +NAN;
			else
				return -NAN;
		}
	}
	else {
		if(exponent==0){
			if(fraction==0){
				if(s=1)
					return +0;
				else
					return -0;
			}
			else
				a1 = pow(2, -1022) * fraction * s;
		}
		else {
			exponent -= 1023;
			a1 = pow(2, exponent) * fraction * s;
		}
	}
	return a1;
}