#include<stdio.h>
#include<math.h>

double calc(int n, int m){
	double res=0.0;
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			res+=i/pow(2, j);
		}
	}
	return res;
}