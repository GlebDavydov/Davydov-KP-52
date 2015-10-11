
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int satisfies(int, int, int);

int main() {
    int aval = 0, bval = 0, cval = 0; 
    int resultVal;
	scanf("%d %d %d", &aval, &bval, &cval);
    resultVal = satisfies(aval, bval, cval);

    printf("%i", resultVal);
    return 0;
}

int satisfies(int a, int b, int c) {
   int result;
 if((a < 0) && (b < 0) && (c < 0)){
		int modmin;
		int sum2;
		if((a <= b) && (a <= c)){
			modmin = abs (a);
			sum2 = b + c;
		}
		else if((b <=c ) &&(b <= a)) {
			modmin = abs (b);
			sum2 = a + c;
		}
		else {
			modmin = abs (c);
			sum2 = b + c;
		}
		int power2;
		if(modmin !=1) {while(modmin>2)
		{
			modmin = modmin/2;
			power2 = modmin%2;
		}}
		else power2 =0;
		result =((modmin < 256) && (power2 == 0) && (sum2 < -256)); 			 
	}
	else if((a >= 0) && (b >= 0) && (c >= 0)) {
		int max;
		int min;
		if((a >= b) && (a >= c)) {
			max = a;
			if(b <= c) 
				min = b;
			else
			min = c;
		}
		else {
			if((b >= c) && (b >= a)){
				max = b;
				if(a <= c)
					min = a;
				else
				min = c;
			}
			else {
				min = a;
				if(b >= c)
					max = b;
				else max = c;
			}
		}
		result =((max * min) < 256);
	}
	else {
		if(a >= 0) {
			if(b >= 0)
				result =(c > -256);
			else {
				if(c >= 0)
					result =(b > -256);
				else
					result =((2 * (b + c)) > -256);
			}
		}
		else {
		if(b >= 0) {
			if(c >= 0)
				result =(a > -256);
			else
				result =((2 * (a + c)) > -256);
			}
		else
			result =((2 * (a + b)) > -256);
		}
	}
   return result;
}
