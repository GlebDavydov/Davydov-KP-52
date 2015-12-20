#include"robots.c"

void printframe(int x, int y){ 
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
	COORD pos; 
	for(pos.Y = y; pos.Y < y + 5; pos.Y++){ 
		for(pos.X = x; pos.X < (x + 22); pos.X++){ 
			if(pos.X == x || pos.X == x+21 || pos.Y == y || pos.Y == y+4){
				SetConsoleCursorPosition(hConsole, pos);
				printf("H");
			}
			else{
				SetConsoleCursorPosition(hConsole, pos); 
				printf(" "); 
			}
		} 
	} 
}

void printHelp(int x, int y, char *help){ 
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
	COORD pos; 
	for(pos.Y = y; pos.Y < y + 5; pos.Y++){ 
		for(pos.X = x; pos.X < (x + 30); pos.X++){ 
			if(pos.X == x || pos.X == x+29 || pos.Y == y || pos.Y == y+4){
				SetConsoleCursorPosition(hConsole, pos);
				printf("*");
			}
			else{
				SetConsoleCursorPosition(hConsole, pos); 
				printf(" "); 
			}
		} 
	} 
	pos.Y = y+2;
	pos.X = x+2;
	SetConsoleCursorPosition(hConsole, pos); 
	printf("%s", help); 
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
		colour = 0x84; 
		SetConsoleTextAttribute(hConsole, colour); 
	} 
	else{ 
		colour = 0x48; 
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
			printHelp(43, 6, help);
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