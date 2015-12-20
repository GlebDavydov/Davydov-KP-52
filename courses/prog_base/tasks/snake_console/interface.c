#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<string.h>
#include<ctype.h>

void printframe(int x, int y){ 
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
	COORD pos; 
	for(pos.Y = y; pos.Y < y + 5; pos.Y++){ 
		for(pos.X = x; pos.X < (x + 22); pos.X++){ 
			SetConsoleCursorPosition(hConsole, pos);
			if((pos.X == x || pos.X == x + 21) && (pos.Y == y || pos.Y == y + 4))
				printf("+");
			else{
				if(pos.X == x)
					printf("[");
				else{
					if(pos.X == x + 21)
						printf("]");
					else
						if(pos.Y == y || pos.Y == y + 4)
							printf("~");
						else
							printf(" ");
				}
			}
		} 
	} 
}

void output(char *string, int x1, int x2, int y1, int y2){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
	COORD pos;
	for(pos.Y = y1; pos.Y < y2; pos.Y++){		
		for(pos.X = x1; pos.X < x2; pos.X++){
			SetConsoleCursorPosition(hConsole, pos);
			if((pos.X == x1 || pos.X == x2 - 1) && (pos.Y == y1 || pos.Y == y2 - 1))
				printf("+");
			else{
				if(pos.X == x1)
					printf("[");
				else{
					if(pos.X == x2 - 1)
						printf("]");
					else
						if(pos.Y == y1 || pos.Y == y2 - 1)
							printf("~");
						else
							printf(" ");
				}
			}
		} 
	}
	pos.X = x1 + 2;
	pos.Y = y1 + 2;
	SetConsoleCursorPosition(hConsole, pos);
	string = strtok(string, "\n");
	puts(string);
	while(string != NULL){
		string = strtok(NULL, "\n");
		pos.Y++;
		pos.X = x1+2;
		SetConsoleCursorPosition(hConsole, pos);
		puts(string);
	}
	printf(string);
}

void input(char *string, int x, int y){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
	COORD pos;
	for(pos.Y = y; pos.Y < y + 5; pos.Y++){ 
		for(pos.X = x; pos.X < x + 27; pos.X++){ 
			SetConsoleCursorPosition(hConsole, pos);
			if((pos.X == x || pos.X == x + 26) && (pos.Y == y || pos.Y == y + 4))
				printf("+");
			else{
				if(pos.X == x)
					printf("[");
				else{
					if(pos.X == x + 26)
						printf("]");
					else
						if(pos.Y == y || pos.Y == y + 4)
							printf("~");
						else
							printf(" ");
				}		
			}
		} 
	} 
	pos.X = x + 2;
	pos.Y = y + 2;
	SetConsoleCursorPosition(hConsole, pos);
	gets(string);
	if(strlen(string)>20){
		system("cls");
		output("Too long. Try again", x, x + 27, y, y + 5);
		system("cls");
		input(string, x, y);
	}
}

void printMenu(char * command[], int selected, int size){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
	COORD pos;
	pos.X = 3; 
	pos.Y = 0; 
	SetConsoleCursorPosition(hConsole, pos); 
	int i; 
	int colour; 
	for(i = 0; i < size; i++){ 
	if(i == selected){ 
		colour = 0x4A; 
		SetConsoleTextAttribute(hConsole, colour); 
	} 
	else{ 
		colour = 0x24; 
		SetConsoleTextAttribute(hConsole, colour); 
	} 
	printframe(pos.X-3, pos.Y); 
	pos.Y+=2; 
	SetConsoleCursorPosition(hConsole, pos); 
	printf("%s", command[i]); 
	pos.Y+=3; 
	SetConsoleCursorPosition(hConsole, pos); 
	colour = 0x0F; 
	SetConsoleTextAttribute(hConsole, colour); 
	} 
} 

int menu(char * command[], int size, char * help, int nocls){ 
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
	COORD pos; 
	pos.X = 0; 
	pos.Y = 0; 
	int selected = 0; 
	int num; 
	int colour; 
		while(1){ 
		colour = 0x0F; 
		SetConsoleTextAttribute(hConsole, colour);
		if(!nocls)
			system("cls");
		printMenu(command, selected, size);
		if(strcmp(help, " ") && strcmp(help, "\n") && strcmp(help, "\0") && strcmp(help, "\t") && strcmp(help, "\r"))
			output(help, 43, 80, 3, 8);
		SetConsoleCursorPosition(hConsole, pos); 
		num = getch(); 
		switch(num){ 
			case 72:
				if((selected > 0)){ 
					selected--; 
					pos.Y--; 
				} 
				break; 
			case 80:
				if((selected < size - 1)){ 
					selected++; 
					pos.Y++; 
				} 
				break; 
			case 13: 
				selected = pos.Y; 
				pos.X = 0; 
				pos.Y = 5; 
				SetConsoleCursorPosition(hConsole, pos); 
			return selected; 
		} 
	} 
}

void cleanArea(int y1, int y2){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	SetConsoleTextAttribute(hConsole, 0x0F);
	for(pos.Y = y1; pos.Y < y2; pos.Y++){
		for(pos.X = 0; pos.X < 80; pos.X++){
			SetConsoleCursorPosition(hConsole, pos);
			printf(" ");
		}
	}
}