#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

int main(){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X=12;
	pos.Y=12;
	int background_color;
	int fmt = background_color | BACKGROUND_INTENSITY;
	int ctrlUP = 12, ctrlDOWN = 12, ctrlLEFT = 12, ctrlRIGHT=12;
	for(;pos.X<=79 - ctrlRIGHT;pos.X++){
		if(pos.X+pos.Y==24||pos.X+pos.Y==79)
				background_color = BACKGROUND_BLUE | BACKGROUND_RED;
		else if(pos.X+pos.Y<79&&pos.X+pos.Y>24)
				background_color = BACKGROUND_RED;
			else 
				background_color = BACKGROUND_GREEN | BACKGROUND_RED;
		fmt = background_color | BACKGROUND_INTENSITY; 
		SetConsoleCursorPosition(hConsole, pos);
		SetConsoleTextAttribute(hConsole, fmt);
		puts("*");
		Sleep(10);
	}
	ctrlRIGHT--;
	while(pos.X!=80&&pos.Y!=25){
		for(;pos.Y<=ctrlDOWN;pos.Y++){
		if(pos.X+pos.Y==24||pos.X+pos.Y==79)
			background_color = BACKGROUND_BLUE | BACKGROUND_RED;
		else if(pos.X+pos.Y<79&&pos.X+pos.Y>24)
				background_color = BACKGROUND_RED;
			else 
				background_color = BACKGROUND_GREEN | BACKGROUND_RED;
		fmt = background_color | BACKGROUND_INTENSITY;
		SetConsoleCursorPosition(hConsole, pos);
		SetConsoleTextAttribute(hConsole, fmt);
		puts("*");
		Sleep(10);
		}
		ctrlDOWN++;
		for(;pos.X>=ctrlLEFT;pos.X--){
		if(pos.X+pos.Y==24||pos.X+pos.Y==79)
			background_color = BACKGROUND_BLUE | BACKGROUND_RED;
		else if(pos.X+pos.Y<79&&pos.X+pos.Y>24)
				background_color = BACKGROUND_RED;
			else 
				background_color = BACKGROUND_GREEN | BACKGROUND_RED;
		fmt = background_color | BACKGROUND_INTENSITY;
		SetConsoleCursorPosition(hConsole, pos);
		SetConsoleTextAttribute(hConsole, fmt);
		puts("*");
		Sleep(10);
		}
		ctrlLEFT--;
		for(;pos.Y>=ctrlUP;pos.Y--){
		if(pos.X+pos.Y==24||pos.X+pos.Y==79)
			background_color = BACKGROUND_BLUE | BACKGROUND_RED;
		else if(pos.X+pos.Y<79&&pos.X+pos.Y>24)
				background_color = BACKGROUND_RED;
			else 
				background_color = BACKGROUND_GREEN | BACKGROUND_RED;
		fmt = background_color | BACKGROUND_INTENSITY;
		SetConsoleCursorPosition(hConsole, pos);
		SetConsoleTextAttribute(hConsole, fmt);
		puts("*");
		Sleep(25);
		}
		ctrlUP--;
		for(;pos.X<=79 - ctrlRIGHT;pos.X++){
		if(pos.X+pos.Y==24||pos.X+pos.Y==79)
				background_color = BACKGROUND_BLUE | BACKGROUND_RED;
		else if(pos.X+pos.Y<79&&pos.X+pos.Y>24)
				background_color = BACKGROUND_RED;
			else 
				background_color = BACKGROUND_GREEN | BACKGROUND_RED;
		fmt = background_color | BACKGROUND_INTENSITY;
		SetConsoleCursorPosition(hConsole, pos);
		SetConsoleTextAttribute(hConsole, fmt);
		puts("*");
		Sleep(10);
	}
	ctrlRIGHT--;
	}
	getchar();
	return 0;
}