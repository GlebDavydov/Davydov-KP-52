#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calc(double, double, double);

int main() {
    double xval = 0, yval = 0, zval = 0; 
    double result;
	scanf("%f %f %f", &xval, &yval, &zval);
    result = calc(xval, yval, zval);

    printf("%.12f", result);
    return 0;
}

double calc(double x, double y, double z) {
   double a;
   double a0, a1, a2;
	if((((x-y)<0)&&((1/z)<1))||(x==0)||(x==y)||(y == 0))
		return NAN;
	else {
		a0 = (pow(x, y++)) / (pow((x - y), (1 / z)));
		a1 = y * 2 + z / x;
		a2 = pow(x, (1 / fabs(sin(y))));
		a = a0 + a1+ a2;
	}
   return a;
}
