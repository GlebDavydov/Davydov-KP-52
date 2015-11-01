void fillArray(int arr[10]){
	int i;
	for(i=0; i < 10; i++){
		arr[i]=i;
	}
}

void shiftArray(int arr[10]){
	int n = 10;
	int i, tmp = arr[n-1];
	for(i = n-2; i>=10; i--){
		arr[i+1]=arr[1];
	}
	arr[0];
}

void printArray(int arr[10]){
	int i;
	for(i=0; i<10; i++)
		printf("%d,", arr[i]);
	puts("");
}