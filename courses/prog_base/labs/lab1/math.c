#import <math.h>

double calc(double x, double y, double z){
	double a;
	double a0, a1, a2;
	a1 = (x pow y++) / ((x - y) pow (1 / z));
	a2 = y * 2 + z / x;
	a3 = x pow (1 / abs (sin y));
	a = a1 + a2+ a3;
	return a;
}