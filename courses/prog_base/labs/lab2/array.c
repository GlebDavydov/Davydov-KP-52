#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

void fillRand3(int arr[], int size){
	srand(time(NULL));
	for(int i = 0; i < size; i++)
		arr[i] = rand()%(2+0);
}

float meanValue(int arr[], int size){
	float res;
	float sum = 0.0;
	for(int i = 0; i < size; i++)
		sum += arr[i];
	res = sum/size;
	return res;
}

int minValue(int arr[], int size){
	int minElem = arr[0];
	for(int i = 0; i < size; i++){
		if(arr[i] < minElem)
			minElem = arr[i];
	}
	return minElem;
}

int meanIndex(int arr[], int size){
	float mean = 0.0;
	int j=0;
	for(int i = 0; i < size; i++)
		mean += arr[i];
	mean = mean/size;
	int closest = arr[0];
	for(int i = 1; i< size; i++){
		if((fabs(mean - (double)closest)) > (fabs(mean - (double)arr[i]))){
			closest = arr[i];
			j = i;
		}
	}
	return j;
}

int minIndex(int arr[], int size){
	int j=0;
	int minElem = arr[0];
	for(int i = 0; i < size; i++){
		if(arr[i] < minElem){
			minElem = arr[i];
			j = i;
		}
	}
	return j;
}

int maxOccurance(int arr[], int size){
	int ctrl[size];
	int occI[size];
	for(int i=0; i < size; i++){
		ctrl[i]=0;
		occI[i]=0;
	}
	for(int i = 0; i < size; i++){
		if(ctrl[i]==1)
			continue;
		for(int j = i; j < size; j++){
			if(arr[i]==arr[j]){
				occI[i]++;
				ctrl[j]=1;
			}
		}
	}
	int maxElem = arr[0];
	int maxOccI = occI[0];
	for(int i=0; i < size; i++){
		if(occI[i]>maxOccI){
			maxElem = arr[i];
			maxOccI = occI[i];
		}
		else if((occI[i])==(maxOccI)){
			maxElem = fmax(arr[i], maxElem);
		} 
	}
	return maxElem;
}

int difference(int arr1[], int arr2[], int res[], int size){
	int ctrl=0;
	for(int i=0; i<size; i++){
		res[i]= arr1[i] - arr2[i];
		if(res[i]==0)
			ctrl++;
	}
	if(ctrl==size)
		return 1;
	else
		return 0;
}

void mult(int arr1[], int arr2[], int res[], int size){
	for(int i=0; i < size; i++){
		res[i] = arr1[i] * arr2[i];
	}
}

int gt(int arr1[], int arr2[], int size){
	for(int i=0; i < size; i++){
		if(arr1[i] <= arr2[i])
			return 0;
	}
	return 1;
}

void land(int arr1[], int arr2[], int res[], int size){
	for(int i=0; i < size; i++){
		if((arr1[i]==1)&&(arr2[i]==1))
			res[i]=1;
		else
			res[i]=0;
	}
}