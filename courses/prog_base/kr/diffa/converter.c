#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<conio.h>

typedef struct binary_time{
	int b_sec[6];
	int b_min[6];
	int b_hour[5];
	int b_mday[5];
	int b_wday[4];
	int b_month[4];
	int b_year[9];
	int b_yday[9];
	int sTinD;
} bTime;

typedef struct tm tm;

int cp2(int, int);

bTime *convert(time_t *current, bTime *binary);

time_t *deconvert(bTime *binary, time_t *real);

int main(){
	char *output = malloc(30);
	time_t atime = time(&atime);
	time_t *aTime = &atime;
	bTime *btime = malloc(sizeof(bTime));
	btime = convert(aTime, btime);
	//printf("%d%d%d%d%d", btime->b_sec[0], btime->b_sec[1], btime->b_sec[2], btime->b_sec[3], btime->b_sec[4]);
	aTime = deconvert(btime, aTime);
	output = ctime(aTime);
	printf("%s", output);
	getch();
	free(output);
	free(btime);
}

int cp2(int n, int i){
	return (n & 1 << i);
}

bTime *convert(time_t *current, bTime *binary){
	if(current == NULL || binary == NULL)
		return NULL;
	tm *realtime = malloc(sizeof(tm));
	if(realtime == NULL)
		return NULL;
	realtime = localtime(current);
	for(int i = 0; i < 9; i++){
		if(i < 4){
			if(cp2(realtime->tm_mon, i))
				binary->b_month[i]  = 1;
			else
				binary->b_month[i] = 0;
			if(cp2(realtime->tm_wday, i))
				binary->b_wday[i]  = 1;
			else
				binary->b_wday[i] = 0;
		}
		if(i < 5){
			if(cp2(realtime->tm_hour, i))
				binary->b_hour[i]  = 1;
			else
				binary->b_hour[i] = 0;
			if(cp2(realtime->tm_mday, i))
				binary->b_mday[i]  = 1;
			else
				binary->b_mday[i] = 0;
		}
		if(i < 6){
			if(cp2(realtime->tm_min, i))
				binary->b_min[i]  = 1;
			else
				binary->b_min[i] = 0;
			if(cp2(realtime->tm_sec, i))
				binary->b_sec[i]  = 1;
			else
				binary->b_sec[i] = 0;
		}
		if(cp2(realtime->tm_year, i))
			binary->b_year[i] = 1;
		else
			binary->b_year[i] = 0;
		if(cp2(realtime->tm_yday, i))
			binary->b_yday[i] = 1;
		else
			binary->b_yday[i] = 0;
	}
	if(realtime->tm_isdst)
		binary->sTinD = 1;
	else
		binary->sTinD = 0;
	free(realtime);
	return binary;
}

time_t *deconvert(bTime *binary, time_t *real){
	if(real == NULL || binary == NULL)
		return NULL;
	tm aCurrent = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	tm *current = &aCurrent;
	for(int i = 0; i < 8; i++){
		if(i < 4){
			if(binary->b_wday[i])
				current->tm_wday += pow(2, i);
			if(binary->b_month[i])
				current->tm_mon += pow(2, i);
		}
		if(i < 5){
			if(binary->b_mday[i])
				current->tm_mday += pow(2, i);
			if(binary->b_hour[i])
				current->tm_hour += pow(2, i);
		}
		if(i < 6){
			if(binary->b_min[i])
				current->tm_min += pow(2, i);
			if(binary->b_sec[i])
				current->tm_sec += pow(2, i);
		}
		if(binary->b_year[i])
			current->tm_year += pow(2, i);
		if(binary->b_yday[i])
			current->tm_yday += pow(2, i);
	}
	if(binary->sTinD)
		current->tm_isdst = 1;
	*real = mktime(current);
	return real;
}