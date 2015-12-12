#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<windows.h>
#include<conio.h>
#include<math.h>

enum Commands{blowup, buildBot, instruction, singleBattle, multiBattle}; 

int fmt;
COORD pos;

void startConsole(){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	fmt = BACKGROUND_BLUE | BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_GREEN;
	setConsoleTextAttribute(hConsole, fmt);
	for(pos.Y = 0; pos.Y < 25; Y++){
		for(pos.X = 0; pos.X < 80; pos.X++){
			setConsoleCursorPosition(hConsole, pos);
			if(pos.Y == 4 || pos.Y == 19)
				puts(">");
			else
				puts(" ");
		}
	}
	pos.X = 0;
	pos.Y = 1;
	setConsoleCursorPosition(hConsole, pos);
	puts("Welcome to Steel Heroes battle simulator!");
}

void outputAsHelp(char *string){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	fmt = BACKGROUND_BLUE | BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_GREEN;
	setConsoleTextAttribute(hConsole, fmt);
	for(pos.Y = 5; pos.Y < 20; pos.y++){
		for(pos.X = 0; pos.X < 80; pos.X++){
			setConsoleCursorPosition(hConsole, pos);
			puts(" ");
		}
	}
	pos.X = 0;
	pos.Y = 5;
	setConsoleCursorPosition(hConsole, pos);
	puts(string);
}

int menuMain(){
	char comm;
	int cursor = 0;
	char *str1 = "use arrow keys to navigate, enter to choose and escape to quit";
	char *str2 = "view FAQ";
	char *str3 = "build new robot";
	char *str4 = "start a singleplayer match";
	char *str5 = "start a multiplayer match";
	char *menu = malloc(1024);
	sprintf(menu, "%s \n%s \n%s \n%s \n%s", str1, str2, str3, str4, str5);
	while(1){
		fmt = BACKGROUND_BLUE | BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_GREEN;
		setConsoleTextAttribute(hConsole, fmt);
		outputAsHelp(menu);
		pos.X = 0;
		pos.Y = 6;
		setConsoleCursorPosition(hConsole, pos);
		fmt = BACKGROUND_GREEN | BACKGROUND_RED;
		setConsoleTextAttribute(hConsole, fmt);
		switch(cursor){
			case 0:
				puts(str2);
				break;
			case 1:
				puts(str3);
				break;
			case 2:
				puts(str4);
				break;
			case 3:
				puts(str5);
				break;
			default:
				break;
		}
		comm = getch();
		switch((int)comm){
			case 27: //escape
				return blowup;
			case 13: //enter
				switch(cursor){
					case 0:
						return instruction;
					case 1:
						return buildBot;
					case 2:
						return singleBattle;
					case 3:
						return multiBattle;
					default:
						break;
				break;
				}
			case 80: //down key
				if(pos.Y > 6)
					cursor--;
				break;
			case 72: //up key
				if(pos.Y < 9)
					cursor++;
				break;
			default:
				break;
		}
	}
	free(menu);
}

void readStr(char *str){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	fmt = BACKGROUND_BLUE | BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_GREEN;
	setConsoleTextAttribute(hConsole, fmt);
	pos.Y = 24;
	for(pos.X = 0; pos.X < 80; pos.X++){
		setConsoleCursorPosition(hConsole, pos);
		puts(" ");
	}
	pos.X = 0;
	setConsoleCursorPosition(hConsole, pos);
	fflush(stdin);
	fgets(str, 30, stdin);
	fclose(stdin);
}

void FAQ(){
	outputAsHelp()
}