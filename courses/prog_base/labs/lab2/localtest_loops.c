#include<stdio.h>
#include<math.h>
#include"loops.c"

void main(){
	int n, m;
	puts("Input n,m");
	scanf("%d %d", &n, &m);
	double res;
	res = calc(n,m);
	printf("%f", res);
}