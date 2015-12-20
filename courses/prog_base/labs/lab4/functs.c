#include"basicInterface.c"

////////////////////////////////////////////////////
//Main menu block
//
int wpStats(int guns){
	char* string = malloc(1024);
	switch(guns){
		case turbolaser:
			sprintf(string, "range = 4\n", string);
			sprintf(string, "%ssplashDamage = 50\n", string);
			sprintf(string, "%sblastDamage = 50\n", string);
			sprintf(string, "%sfirerate = 1\n", string);
			sprintf(string, "%scritChance = 0.2\n", string);
			sprintf(string, "%saccuracy = 0.75\n", string);
		break;
		case plasmagun:
			sprintf(string, "range = 2\n", string);
			sprintf(string, "%ssplashDamage = 70\n", string);
			sprintf(string, "%sblastDamage = 100\n", string);
			sprintf(string, "%sfirerate = 1\n", string);
			sprintf(string, "%scritChance = 0.4\n", string);
			sprintf(string, "%saccuracy = 0.67\n", string);
		break;
		case bolter:
			sprintf(string, "range = 3\n", string);
			sprintf(string, "%ssplashDamage = 25\n", string);
			sprintf(string, "%sblastDamage = 10\n", string);
			sprintf(string, "%sfirerate = 4\n", string);
			sprintf(string, "%scritChance = 0.1\n", string);
			sprintf(string, "%saccuracy = 0.5\n", string);
		break;
		case rocketpod:
			sprintf(string, "range = -4\n", string);
			sprintf(string, "%ssplashDamage = 50\n", string);
			sprintf(string, "%sblastDamage = 15\n", string);
			sprintf(string, "%sfirerate = 2\n", string);
			sprintf(string, "%scritChance = 0.3\n", string);
			sprintf(string, "%saccuracy = 0.67\n", string);
		break;
		case powerfist:
			sprintf(string, "range = 0\n", string);
			sprintf(string, "%ssplashDamage = 50\n", string);
			sprintf(string, "%sblastDamage = 50\n", string);
			sprintf(string, "%sfirerate = 1\n", string);
			sprintf(string, "%scritChance = 0.5\n", string);
			sprintf(string, "%saccuracy = 1.0\n", string);
		break;
		case powerclaw:
			sprintf(string, "range = 0\n", string);
			sprintf(string, "%ssplashDamage = 30\n", string);
			sprintf(string, "%sblastDamage = 10\n", string);
			sprintf(string, "%sfirerate = 2\n", string);
			sprintf(string, "%scritChance = 0.5\n", string);
			sprintf(string, "%saccuracy = 1.0\n", string);
		break;
		case inferno:
			sprintf(string, "range = 1\n", string);
			sprintf(string, "%ssplashDamage = 15\n", string);
			sprintf(string, "%sblastDamage = 10\n", string);
			sprintf(string, "%sfirerate = 3\n", string);
			sprintf(string, "%scritChance = 0.1\n", string);
			sprintf(string, "%saccuracy = 1.0\n", string);
		break;
		case predator:
			sprintf(string, "range = -4\n", string);
			sprintf(string, "%ssplashDamage = 30\n", string);
			sprintf(string, "%sblastDamage = 25\n", string);
			sprintf(string, "%sfirerate = 1\n", string);
			sprintf(string, "%scritChance = 0.3\n", string);
			sprintf(string, "%saccuracy = 1.0\n", string);
		break;
		case shredder:
			sprintf(string, "range = 0\n", string);
			sprintf(string, "%ssplashDamage = 10\n", string);
			sprintf(string, "%sblastDamage = 1\n", string);
			sprintf(string, "%sfirerate = 4\n", string);
			sprintf(string, "%scritChance = 0.5\n", string);
			sprintf(string, "%saccuracy = 1.0\n", string);
		break;
		case defiler:
			sprintf(string, "range = 4\n", string);
			sprintf(string, "%ssplashDamage = 30\n", string);
			sprintf(string, "%sblastDamage = 15\n", string);
			sprintf(string, "%sfirerate = 2\n", string);
			sprintf(string, "%scritChance = 0.2\n", string);
			sprintf(string, "%saccuracy = 0.75\n", string);
		break;
		case volcano:
			sprintf(string, "range = 3\n");
			sprintf(string, "%ssplashDamage = 75\n", string);
			sprintf(string, "%sblastDamage = 75\n", string);
			sprintf(string, "%sfirerate = 1\n", string);
			sprintf(string, "%scritChance = 0\n", string);
			sprintf(string, "%saccuracy = 100\n", string);
		break;
	}
	system("cls");
	output(string, 19, 60, 4, 20);
	getch();	
	char* commands[] = {"Apply", "Cancel"};
	free(string);
	return menu(commands, 2, " ", 0);
}

int botStats(int pattern){
	char* string = malloc(1024);
	switch(pattern){
		case lucius:
			sprintf(string, "speed = 3\n");
			sprintf(string, "%sarmor = 30\n", string);
			sprintf(string, "%sshield = 45\n", string);
			sprintf(string, "%shitpoints = 250\n", string);
			sprintf(string, "%sslots = 2\n", string);
		break;
		case contemptor:
			sprintf(string, "speed = 1\n");
			sprintf(string, "%sarmor = 35\n", string);
			sprintf(string, "%sshield = 30\n", string);
			sprintf(string, "%shitpoints = 300\n", string);
			sprintf(string, "%sslots = 3\n", string);
		break;
		case mars:
			sprintf(string, "speed = 2\n");
			sprintf(string, "%sarmor = 35\n", string);
			sprintf(string, "%sshield = 28\n", string);
			sprintf(string, "%shitpoints = 220\n", string);
			sprintf(string, "%sslots = 3\n", string);
		break;
		case phobos:
			sprintf(string, "speed = 4\n");
			sprintf(string, "%sarmor = 35\n", string);
			sprintf(string, "%sshield = 22\n", string);
			sprintf(string, "%shitpoints = 250\n", string);
			sprintf(string, "%sslots = 2\n", string);
		break;
		case graia:
			sprintf(string, "speed = 2\n");
			sprintf(string, "%sarmor = 40\n", string);
			sprintf(string, "%sshield = 40\n", string);
			sprintf(string, "%shitpoints = 300\n", string);
			sprintf(string, "%sslots = 2\n", string);
		break;
	}
	system("cls");
	output(string, 19, 60, 4, 20);
	getch();	
	char* commands[] = {"Apply", "Cancel"};
	free(string);
	return menu(commands, 2, " ", 0);
}

void *gunConstructor(Weapon* wp){
	char *commands[] = {"turbolaser", "plasmagun", "bolter", "rocketpod", "powerfist", "powerclaw", "inferno", "predator", "shredder", "defiler", "volcano"};
	int a;
	int b;
	do{
		a = menu(commands, 11, "choose the weapon", 0);
		b = wpStats(a);
	}while(b);
	gunAssemble(wp, a);
}

void saveBot(Robot *bot){
	FILE *fp;
	char str[100];
	sprintf(str, "%s.txt", bot->name);
	if ((fp = fopen(str, "wb"))== NULL) {
		output("TOO BAD, LOOKS LIKE SAVES FILE CORRUPTED!\n", 0, 80, 0, 25);
		exit(0);
	}
	fwrite(bot, sizeof(Robot), 1, fp);
	fclose(fp);
}

int deleteBot(char *string){
	FILE *fp;
	char str[100];
	sprintf(str, "%s.txt", string);
	if((fp = fopen(str, "r"))== NULL){
		return 0;
	}
	fclose(fp);
	char str2[100];
	sprintf(str2, "del %s", str);
	system(str2);
	return 1;
}

void loadBot(Robot *bot, char *name){
	FILE *fp;
	char str[100];
	sprintf(str, "%s.txt", name);
	if ((fp = fopen(str, "rb")) == NULL){
		system("cls");
		output("Sorry, no such bot found", 49, 80, 4, 10);
		getch();
		return NULL;
	}
	fread(bot, sizeof(Robot), 1, fp);
	fclose(fp);
}

int robotConstructor(void){
	char *commands[] = {"Quit", "Lucius", "Contemptor", "Mars", "Phobos", "Graia"};
	int a; //robot pattern
	int b; //confirmation
	do{
		a = menu(commands, 6, "choose the robot pattern", 0);
		if(!a)
			return 0;
	b = botStats(a);	
	}while(b);
	Robot *newBot = malloc(sizeof(Robot));
	Weapon *wp1 = malloc(sizeof(Weapon));
	gunConstructor(wp1);
	Weapon *wp2 = malloc(sizeof(Weapon));
	gunConstructor(wp2);
	Weapon *wp3 = malloc(sizeof(Weapon));
	if(a == contemptor || a == mars)
		gunConstructor(wp3);
	else
		gunAssemble(wp3, none);
	botAssemble(newBot, a, wp1, wp2, wp3);
	saveBot(newBot);
	free(newBot);
	free(wp1);
	free(wp2);
	free(wp3);
	return 0;
}

void instruction(void){
	FILE *fp;
	if((fp = fopen("faq12345678901234567890.txt", "r")) == NULL){
		system("cls");
		output("Oops, looks like FAQ file is lost\n", 0, 80, 0, 25);
		exit(0);
	}
	char a[10000];
	fgets(a, 10000, fp);
	system("cls");
	output(a, 0, 80, 0, 50);
	getch();
	fclose(fp);
}

//////////////////////////////////////////////////////
//Battle block
//
void printBot(int position, int clr, int hp){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
	COORD pos; 
	pos.X = 37 + (5*position); 
	pos.Y = 19; 
	SetConsoleCursorPosition(hConsole, pos); 
	FILE * fp; 
	char str[10]; 
	int i;
	if(!clr)
		fp = fopen("RED12345678901234567890.txt", "r"); 
	else
		fp = fopen("BLUE12345678901234567890.txt", "r");
	if (NULL == fp) { 
		exit(EXIT_FAILURE); 
	} 
	while(!feof(fp)){ 
		fgets(str, 10, fp);
		for(i = 0; i < 5; i++){
			switch(str[i]){ 
			case '0': 
				SetConsoleTextAttribute(hConsole, 0x0F); //black
				break; 
			case '1': 
				if(!clr)
					SetConsoleTextAttribute(hConsole, 0x4F); //red 
				else
					SetConsoleTextAttribute(hConsole, 0x1F); //blue
				break; 
			case '2':
				if(!clr)
					SetConsoleTextAttribute(hConsole, 0xCF); //bright red 
				else
					SetConsoleTextAttribute(hConsole, 0x9F); //bright blue
				break; 
			case '3': 
				SetConsoleTextAttribute(hConsole, 0x8F); //dark grey
				break;  
			case '4': 
				SetConsoleTextAttribute(hConsole, 0x7F); //grey
				break; 
			case '5': 
				SetConsoleTextAttribute(hConsole, 0xEF); //bright yellow
				break; 
			} 
			printf(" "); 
		} 
		printf("\n"); 
		pos.Y++; 
		SetConsoleCursorPosition(hConsole, pos); 
	} 
	fclose(fp);
	pos.Y++;
	pos.X++;
	SetConsoleCursorPosition(hConsole, pos);
	if(hp >= 200)
		SetConsoleTextAttribute(hConsole, 0x20);
	else if(hp >= 100)
		SetConsoleTextAttribute(hConsole, 0x60);
	else
		SetConsoleTextAttribute(hConsole, 0x40);
	printf("%d", hp);
	if(clr){
		pos.Y++;
		for(pos.X = 0; pos.X < 80; pos.X++){
			if((abs(39 - pos.X) % 5) == 0){
				SetConsoleCursorPosition(hConsole, pos);
				SetConsoleTextAttribute(hConsole, 0xCF);
				printf("%d", (abs(39 - pos.X) / 5));
			}
			else{ 
			SetConsoleCursorPosition(hConsole, pos);
			SetConsoleTextAttribute(hConsole, 0xF0);
			printf(" ");
			}
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

void printBotStats(Robot *bot1, Robot *bot2){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 0x0F);
	system("cls");
	char* string1 = malloc(1024);
	char* string2 = malloc(1024);
	string1 = formBotStats(bot1, string1);
	output(string1, 0, 40, 12, 50);
	string2 = formBotStats(bot2, string2);
	output(string2, 40, 80, 12, 50);
	getch();
	free(string1);
	free(string2);
}

void shoot(Weapon wp, Robot	*target){
	srand(time(NULL));
	char *str = malloc(100);
	for(int i = 1; i <= wp.firerate; i++){
		double tmp = 1 / (1 - wp.accuracy);
		int chance = tmp;
		if(rand()%chance){
			int eDamage = ((wp.blastDamage * (1.0 - (double)((target->shield)/100))) * 2 )/ 3;
			int damage = (wp.splashDamage * (1.0 - (double)(((target->armor)+(target->shield / 2))/100))) + eDamage;
			if(wp.critChance != 0){
				tmp = 1 / wp.critChance;
				chance = tmp;
				if(!rand()%chance){
					output("Dealt a Critical hit!", 24, 55, 9, 15);
					Sleep(1500);
					damage = (damage * 3) / 2;
					eDamage = (eDamage *3) / 2;
				}
			}
			target->hitpoints -= damage;
			target->shield -= (eDamage / 2);
			sprintf(str, "Dealt %d damage", damage);
			output(str, 24, 55, 9, 15);
			Sleep(1500);
		}
		else
			output("miss", 24, 55, 9, 15);
			Sleep(1500);
	}
	free(str);
}

int startMultiBattle(Robot *red, Robot *blue, char *name1, char *name2){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	char stmp[100] = "CONTROLS:\nQuit\tEscape\nMove\tArrow keys\nFire 1\t1\nFire 2\t2\nFire 3\t3\nEnd turn\tSpace\nCurrent stats\tp";
	system("cls");
	output(stmp, 19, 60, 4, 20);
	getch();
	system("cls");
	output(name1, 0, 20, 0, 5);
	output(red->name, 0, 20, 6, 11);
	output(name2, 59, 80, 0, 5);
	output(blue->name, 59, 80, 6, 11);
	int redPos = -3;
	int bluePos = 3;
	int redShieldMax = red->shield;
	int blueShieldMax = blue->shield;
	cleanArea(12, 20);
	printBot(redPos, 0, red->hitpoints);
	printBot(bluePos, 1, blue->hitpoints);
	int status = 0;
	while(red->hitpoints > 0 && blue->hitpoints > 0){
		//RedTurnBlock
			output("Player 1 turn", 21, 58, 0, 5);
			for(int i = 1; i <= 5 && red->shield < redShieldMax; i++)
				red->shield++;
			char ch;
			int moveACT = red->speed;
			int gunStatus[3] = {1, 1};
			if(red->weapon3.blastDamage == 0)
				gunStatus[2] = 0;
			else
				gunStatus[2] = 1;
			while(ch != ' ' && !status){
				SetConsoleTextAttribute(hConsole, 0x0F);
				system("cls");
				output(name1, 0, 20, 0, 5);
				output(red->name, 0, 20, 6, 11);
				output(name2, 59, 80, 0, 5);
				output(blue->name, 59, 80, 6, 11);
				cleanArea(12, 50);
				printBot(redPos, 0, red->hitpoints);
				printBot(bluePos, 1, blue->hitpoints);
				output("Player 1 turn", 21, 58, 0, 5);
				ch = getch();
				switch(ch){
					case 27:
						return 0;
					case 'p':
						printBotStats(red, blue);
						system("cls");
						break;
					case 75: //left
						if(moveACT != 0){
							if(redPos + 1 <= 9){
								redPos--;
								moveACT--;
							}
							else{
								output("No retreat!", 24, 55, 9, 15);
								Sleep(1500);
							}
						}
						else{
							output("insufficient speed", 24, 55, 9, 15);
							Sleep(1500);
						}
						break;
					case 77: //right
						if(moveACT != 0){
							if(redPos +1 != bluePos){
								redPos++;
								moveACT--;
							}
							else{
								output("Collision", 24, 55, 9, 15);
							Sleep(1500);
							}
						}
						else{
							output("insufficient speed", 24, 55, 9, 15);
							Sleep(1500);
						}
						break;
					case '1':
						if(gunStatus[0]){
							if((abs(red->weapon1.range)) * 2 >= (bluePos - redPos) || ((red->weapon1.range == 0) && (bluePos - redPos < 2))){
								if(!(red->weapon1.range < 0 && (bluePos - redPos < 2))){
									shoot(red->weapon1, blue);
									gunStatus[0]--;
									if(blue->hitpoints <= 0)
										status = 1;
								}
								else{
									output("too close for explosives", 24, 55, 9, 15);
									Sleep(1500);
								}
							}
							else{
								output("out of range", 24, 55, 9, 15);
								Sleep(1500);
							}
						}
						else{
							output("Gun may not be used", 24, 55, 9, 15);
							Sleep(1500);
						}
						break;
						case '2':
						if(gunStatus[1]){
							if((abs(red->weapon2.range)) * 2 >= (bluePos - redPos) || ((red->weapon2.range == 0) && (bluePos - redPos < 2))){
								if(!(red->weapon2.range < 0 && (bluePos - redPos < 2))){
									shoot(red->weapon2, blue);
									gunStatus[1]--;
									if(blue->hitpoints <= 0)
										status = 1;
								}
								else{
									output("too close for explosives", 24, 55, 9, 15);
									Sleep(1500);
								}
							}
							else{
								output("out of range", 24, 55, 9, 15);
								Sleep(1500);
							}
						}
						else{
							output("Gun may not be used", 24, 55, 9, 15);
							Sleep(1500);
						}
						break;
						case '3':
						if(gunStatus[2]){
							if((abs(red->weapon3.range)) * 2 >= (bluePos - redPos) || ((red->weapon3.range == 0) && (bluePos - redPos < 2))){
								if(!(red->weapon3.range < 0 && (bluePos - redPos < 2))){
									shoot(red->weapon3, blue);
									gunStatus[2]--;
									if(blue->hitpoints <= 0)
										status = 1;
								}
								else{
									output("too close for explosives", 24, 55, 9, 15);
									Sleep(1500);
								}
							}
							else{
								output("out of range", 24, 55, 9, 15);
								Sleep(1500);
							}
						}
						else{
							output("Gun may not be used", 24, 55, 9, 15);
							Sleep(1500);
						}
						break;
				}
			}
		//BlueTurnBlock
		ch = 0;
		output("Player 2 turn", 21, 58, 0, 5);
		if(status == 0){
			for(int i = 1; i <= 5 && blue->shield < blueShieldMax; i++)
				blue->shield++;
			moveACT = blue->speed;
			gunStatus[0] = 1;
			gunStatus[1] = 1;
			if(blue->weapon3.blastDamage == 0)
				gunStatus[2] = 0;
			else
				gunStatus[2] = 1;
			while(ch != ' '){
				SetConsoleTextAttribute(hConsole, 0x0F);
				system("cls");
				output(name1, 0, 20, 0, 5);
				output(blue->name, 0, 20, 6, 11);
				output(name2, 59, 80, 0, 5);
				output(blue->name, 59, 80, 6, 11);
				cleanArea(12, 50);
				printBot(redPos, 0, red->hitpoints);
				printBot(bluePos, 1, blue->hitpoints);
				output("Player 2 turn", 21, 58, 0, 5);
				ch = getch();
				switch(ch){
					case 27:
						SetConsoleTextAttribute(hConsole, 0x0F);
						system("cls");
						return 0;
					case 'p':
						printBotStats(red, blue);
						break;
					case 77: //right
						if(moveACT != 0){
							if(bluePos + 1 <= 9){
								bluePos++;
								moveACT--;
							}
							else{
								output("No retreat!", 24, 55, 9, 15);
								Sleep(1500);
							}
						}
						else{
							output("insufficient speed", 24, 55, 9, 15);
							Sleep(1500);
						}
						break;
					case 75: //left
						if(moveACT != 0){
							if(redPos +1 != bluePos){
								bluePos--;
								moveACT--;
							}
							else{
								output("Collision", 24, 55, 9, 15);
							Sleep(1500);
							}
						}
						else{
							output("insufficient speed", 24, 55, 9, 15);
							Sleep(1500);
						}
						break;
					case '1':
						if(gunStatus[0]){
							if((abs(blue->weapon1.range)) * 2 >= (bluePos - redPos) || ((blue->weapon1.range == 0) && (bluePos - redPos < 2))){
								if(!(blue->weapon1.range < 0 && (bluePos - redPos < 2))){
									shoot(blue->weapon1, red);
									gunStatus[0]--;
									if(red->hitpoints <= 0)
										status = 2;
								}
								else{
									output("too close for explosives", 24, 55, 9, 15);
									Sleep(1500);
								}
							}
							else{
								output("out of range", 24, 55, 9, 15);
								Sleep(1500);
							}
						}
						else{
							output("Gun may not be used", 24, 55, 9, 15);
							Sleep(1500);
						}
						break;
						case '2':
						if(gunStatus[1]){
							if((abs(blue->weapon2.range)) * 2 >= (bluePos - redPos) || ((blue->weapon2.range == 0) && (bluePos - redPos < 2))){
								if(!(blue->weapon2.range < 0 && (bluePos - redPos < 2))){
									shoot(blue->weapon2, red);
									gunStatus[1]--;
									if(red->hitpoints <= 0)
										status = 2;
								}
								else{
									output("too close for explosives", 24, 55, 9, 15);
									Sleep(1500);
								}
							}
							else{
								output("out of range", 24, 55, 9, 15);
								Sleep(1500);
							}
						}
						else{
							output("Gun may not be used", 24, 55, 9, 15);
							Sleep(1500);
						}
						break;
						case '3':
						if(gunStatus[2]){
							if((abs(blue->weapon3.range)) * 2 >= (bluePos - redPos) || ((blue->weapon3.range == 0) && (bluePos - redPos < 2))){
								if(!(blue->weapon3.range < 0 && (bluePos - redPos < 2))){
									shoot(blue->weapon3, red);
									gunStatus[2]--;
									if(red->hitpoints <= 0)
										status = 2;
								}
								else{
									output("too close for explosives", 24, 55, 9, 15);
									Sleep(1500);
								}
							}
							else{
								output("out of range", 24, 55, 9, 15);
								Sleep(1500);
							}
						}
						else{
							output("Gun may not be used", 24, 55, 9, 15);
							Sleep(1500);
						}
						break;
				}
			}
		}
		ch = 0;
		//End turn
	}
	char *tmp = malloc(50);
	SetConsoleTextAttribute(hConsole, 0x5E);
	switch(status){
		case 1:
			sprintf(tmp, "%s is a winner!", name1);
			break;
		case 2:
			sprintf(tmp, "%s is a winner!", name2);
			break;
	}
	output(tmp, 24, 55, 9, 15);
	getch();
	SetConsoleTextAttribute(hConsole, 0x0F);
	free(tmp);
	system("cls");
	return 0;
}