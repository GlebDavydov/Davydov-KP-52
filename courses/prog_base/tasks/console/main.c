#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

void main(){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X=13;
	pos.Y=13;
	int background_color;
	int fmt = background_color | BACKGROUND_INTENSITY;
	int ctrlUP = 13, ctrlDOWN = 13, ctrlLEFT = 13, ctrlRIGHT=13;
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
}