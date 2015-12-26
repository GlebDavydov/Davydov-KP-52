#include<windows.h>
#include<time.h>
#include<stdio.h>
#include<conio.h>

typedef struct tm tm;

void printtime(tm *cl);

int cp2(int n, int i);

int main(){
	time_t ptimer;
	tm *cl1 = malloc(sizeof(tm));
	while(1){
		Sleep(1000);
		time(&ptimer);
		cl1 = localtime(&ptimer);
		printtime(cl1);
	}
	free(cl1);
	return 0;
}

int cp2(int n, int i){
	return (n & 1 << i);
}

void printtime(tm *cl){
	system("cls");
	COORD pos;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	pos.X = 33;
	pos.Y = 9;
	SetConsoleCursorPosition(hConsole, pos);
	printf("%d:%d:%d", cl->tm_hour, cl->tm_min, cl->tm_sec);
	int arrH[8] = {0};
	int arrM[8] = {0};	
	int arrS[8] = {0};
	int a1, a2, a3, b1, b2, b3;
	a1 = cl->tm_hour % 10;
	b1 = cl->tm_hour / 10;
	a2 = cl->tm_min % 10;
	b2 = cl->tm_min / 10;
	a3 = cl->tm_sec % 10;
	b3 = cl->tm_sec / 10;
	for(int i = 0; i < 4; i++){
		if(cp2(a1, i))
			arrH[7 - i] = 1;
		if(cp2(b1, i))
			arrH[3 - i] = 1;
		if(cp2(a2, i))
			arrM[7 - i] = 1;
		if(cp2(b2, i))
			arrM[3 - i] = 1;
		if(cp2(a3, i))
			arrS[7 - i] = 1;
		if(cp2(b3, i))
			arrS[3 - i] = 1;
	}
	if(cp2)
	for(int i = 0; i < 8; i++){
		pos.Y = 12 + i % 4;
		pos.X = 32 + i / 4;
		SetConsoleCursorPosition(hConsole, pos);
		if(arrH[i])
			SetConsoleTextAttribute(hConsole, 0xff);
		else
			SetConsoleTextAttribute(hConsole, 0x0f);
		printf(" ");
		pos.Y = 12 + i % 4;
		pos.X = 35 + i / 4;
		SetConsoleCursorPosition(hConsole, pos);
		if(arrM[i])
			SetConsoleTextAttribute(hConsole, 0xff);
		else
			SetConsoleTextAttribute(hConsole, 0x0f);
		printf(" ");
		pos.Y = 12 + i % 4;
		pos.X = 38 + i / 4;
		SetConsoleCursorPosition(hConsole, pos);
		if(arrS[i])
			SetConsoleTextAttribute(hConsole, 0xff);
		else
			SetConsoleTextAttribute(hConsole, 0x0f);
		printf(" ");
		SetConsoleTextAttribute(hConsole, 0x0f);
	}
}