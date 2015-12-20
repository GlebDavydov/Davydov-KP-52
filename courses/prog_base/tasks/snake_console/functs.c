#include"interface.c"

typedef struct snakie1{
	int x;
	int y;
} Asp;

int moves(int level, char *name);

int gameMenu(char *, char *);

void saveScore(char *record){
	FILE *fp;
	if((fp = fopen("scores.txt", "a")) == NULL){
		exit(EXIT_FAILURE);
	}
	fputs(record, fp);
	fclose(fp);
}

void sortScores(char *string, int counter){
	int scores[counter];
	char *pString[295];
	char *p = malloc(22420);
	strcpy(p, string);
	for(int i = 0; i < counter; i++){
		p = strtok(p, "\n");
		strcpy(p, pString[i]);
		while(p != NULL){
			p = (NULL, "\n");
			strcpy(p, pString[i]);
		}
	}
	for(int i = 0; i < counter; i++){
		strcpy(p, pString[i]);
		p = strtok(p, " ");
		strcpy(p, pString[i]);
		while(p != NULL){
			p = (NULL, " ");
			strcpy(p, pString[i]);
		}
		sscanf(p, "%d", &scores[i]);
	}
	int pos;
	int buffer;
	char strBuffer[73];
    for (int i = 0; i < counter; i ++){
		if(i != counter - 1){
			for (int j = i + 1 ; j < counter; j++){
				if(scores[pos] > scores[j])
					pos = j;
			}
			if (pos != i){ 
				buffer = scores[i];
				strcpy(strBuffer, pString[i]);
				scores[i] = scores[pos];
				strcpy(pString[i], pString[pos]);
				scores[pos] = buffer;
				strcpy(pString[pos], strBuffer);
			}
		}
		sprintf(string, "%s\n%d.%s", string, i+1, pString);
	}
	free(p);
}

int viewHighsores(void){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	FILE *fp;
	if((fp = fopen("scores.txt", "r")) == NULL){
		output("Oops! Scores files corrupted!", 27, 62, 4, 9);
		getch();
		return 0;
	}
	char string[73];
	char final[22420] = "\n";
	int i = 0;
	int status = 0;
	while(!feof(fp) && i < 73 && !status){
		fgets(string, 295, fp);
		i++;
		if(string == NULL)
			status = 1;
		sprintf(final, "%s\n%d.%s", final, i, string);
	}
	//sortScores(final, i);
	output(final, 0, 80, 0, 300);
	getch();
	fclose(fp);
	return 0;
}

int menuMain(void){
	char name[20];
	name[0] = '\0';
	enum comm{blowup, cName, hiscore, play};
	char *commands[] = {"Quit", "Change name", "View scoreboard", "Start game"};
	int st = 0;
	char record[73];
	while(1){
		switch(menu(commands, 4, name, 0)){
			case blowup:
				return 0;
			case cName:
				input(name, 26, 0);
				st = 1;
				break;
			case hiscore:
				viewHighsores();
				break;
			case play:
				if(st){
					gameMenu(record, name);
					saveScore(record);
				}
				else{
					output(("You should input your name first"), 39, 80, 0, 5);
					getch();
				}
				break;
		}
	}
}

int moves(int level, char *name){
	srand(time(NULL));
	system("cls");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	Asp snake[1794] = {0};
	SetConsoleTextAttribute(hConsole, 0x5E);
	output("", 0, 80, 0, 25);
	pos.Y = 0;
	pos.X = 0;
	SetConsoleCursorPosition(hConsole, pos);
	printf("%s", name);
	pos.X = 35;
	SetConsoleCursorPosition(hConsole, pos);
	printf("Level: %d", level);
	SetConsoleTextAttribute(hConsole, 0x0F);
	cleanArea(1, 24);
	int crash = 0;
	int score = 0;
	int length = 5;
	snake[0].x = 40;
	snake[0].y = 12;
	snake[1].x = 39;
	snake[1].y = 12;
	snake[2].x = 38;
	snake[2].y = 12;
	snake[3].x = 37;
	snake[3].y = 12;
	snake[4].x = 36;
	snake[4].y = 12;
	int fieldStatus[80][25] = {0};
	for(int i = 0; i < length; i++){
		SetConsoleTextAttribute(hConsole, 0x2F);
		pos.X = snake[i].x;
		pos.Y = snake[i].y;
		SetConsoleCursorPosition(hConsole, pos);
		fieldStatus[snake[i].x][snake[i].y] = 1;
		printf(" ");
	}
	int apple[2];
	int eat_Status = 0;
	int random_Status;
	enum directions{Up = 72, Down = 80, Left = 75, Right = 77};
	int direction = Right;
	int newDir;
	int slt = 500 - 50 * level;
	char result[100];
	while(!crash){
		SetConsoleTextAttribute(hConsole, 0x5E);
		pos.Y = 0;
		pos.X = 65;
		SetConsoleCursorPosition(hConsole, pos);
		printf("Score: %d", score);
		eat_Status = 0;
		do{
			random_Status = 0;
			apple[0] = rand()% 78 + 1;
			apple[1] = rand()% 23 + 1;
			for(int i = 0; i < length; i++){
				if(snake[i].x == apple[0] && snake[i].y == apple[1])
				random_Status = 1;
			}
		}while(random_Status);
		pos.X = apple[0];
		pos.Y = apple[1];
		SetConsoleCursorPosition(hConsole, pos);
		SetConsoleTextAttribute(hConsole, 0x3F);
		printf(" ");
		while(!eat_Status && !crash){
			while(!kbhit() && !crash){
				Sleep(slt);
				switch(direction){
					case Left:
						snake[0].x--;
					break;
					case Right:
						snake[0].x++;
					break;
					case Up:
						snake[0].y--;
					break;
					case Down:
						snake[0].y++;
					break;
				}
				if(snake[0].x == -1)
					snake[0].x = 78;
				if(snake[0].x == 79)
					snake[0].x = 1;
				if(snake[0].y == 0)
					snake[0].y = 23;
				if(snake[0].y == 24)
					snake[0].y = 1;
				if(!fieldStatus[snake[0].x][snake[0].y]){	
					if(snake[0].x == apple[0] && snake[0].y == apple[1]){
						eat_Status = 2;
					}
					for(int i = 0; i < 1840; i++)
						fieldStatus[i % 80][i / 80] = 0;
					pos.X = snake[length - 1].x;
					pos.Y = snake[length - 1].y;
					SetConsoleCursorPosition(hConsole, pos);
					SetConsoleTextAttribute(hConsole, 0x0F);
					printf(" ");
					pos.X = 0;
					pos.Y = 0;
					SetConsoleCursorPosition(hConsole, pos);
					for(int i = length - 1; i > 0; i--){
						snake[i].x = snake[i - 1].x;
						snake[i].y = snake[i - 1].y;
					}
					for(int i = 0; i < length; i++){
						SetConsoleTextAttribute(hConsole, 0x2F);
						pos.X = snake[i].x;
						pos.Y = snake[i].y;
						SetConsoleCursorPosition(hConsole, pos);
						fieldStatus[snake[i].x][snake[i].y] = 1;
						printf(" ");
					}
					if(eat_Status == 2 && snake[length - 1].x == apple[0] && snake[length - 1].y == apple[1]){
						length++;
						score++;
						if(!(score % 10) && level < 9){
							level++;
							slt -= 50;
							SetConsoleTextAttribute(hConsole, 0x5E);
							pos.Y = 0;
							pos.X = 35;
							SetConsoleCursorPosition(hConsole, pos);
							printf("Level: %d", level);
						}
						eat_Status = 1;
					}
				}
				else crash = 1;
			}
			if(kbhit()){
				newDir = getch();
				switch(newDir){
				case Left:
					if(direction != Right){
						direction = Left;
					}
					break;
				case Right:
					if(direction != Left){
						direction = Right;
					}
					break;
				case Up:
					if(direction != Down){
						direction = Up;
					}
					break;
				case Down:
					if(direction != Up){
						direction = Down;
					}
					break;
				case 27:
					SetConsoleTextAttribute(hConsole, 0x4A);
					sprintf(result, "Game over. Your score: %d", score);
					output(result, 24, 55, 9, 15);
					getch();
					system("cls");
					return score;	
				}
			}
		}
	}
	SetConsoleTextAttribute(hConsole, 0x4A);
	sprintf(result, "CRASH! Game over.\nYour score: %d", score);
	output(result, 24, 55, 9, 15);
	getch();
	system("cls");
	return score;
}

int gameMenu(char *record, char *name){
	enum comm{blowup, lvl1, lvl2, lvl3, lvl4, lvl5, lvl6, lvl7, lvl8, lvl9};	
	char *commands[] = {"Quit", "Earthworm", "Adder", "Asp", "Viper", "Python", "Anaconda", "Cobra", "Black Mamba", "Hydra of Lerneia"};
	int scores = 0;
	int status = 0;
	while(!status){
		switch(menu(commands, 10, "Choose level", 0)){
			case blowup:
				return 0;
			case lvl1:
				scores = moves(1, name);
				status = 1;
				break;
			case lvl2:
				scores = moves(2, name);
				status = 2;
				break;
			case lvl3:
				scores = moves(3, name);
				status = 3;
				break;
			case lvl4:
				scores = moves(4, name);
				status = 4;
				break;
			case lvl5:
				scores = moves(5, name);
				status = 5;
				break;
			case lvl6:
				scores = moves(6, name);
				status = 6;
				break;
			case lvl7:
				scores = moves(7, name);
				status = 7;
				break;
			case lvl8:
				scores = moves(8, name);
				status = 8;
				break;
			case lvl9:
				scores = moves(9, name);
				status = 9;
				break;
		}
	}
	sprintf(record, "%s (level: %d) %d \n", name, status, scores);
	return 0;
}