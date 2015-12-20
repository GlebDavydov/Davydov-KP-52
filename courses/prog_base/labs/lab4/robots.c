#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<windows.h>
#include<conio.h>
#include<math.h>
#include<time.h>
//done
enum weapons{turbolaser, plasmagun, bolter, rocketpod, powerfist, powerclaw, inferno, predator, shredder, defiler, volcano, none};
enum robotPatterns{lucius = 1, contemptor, mars, phobos, graia};

typedef struct RobotWeapon{
	int range;
	int splashDamage;
	int blastDamage;
	int firerate;
	double critChance;
	double accuracy;
} Weapon;

typedef struct BattleRobot{
	char name[20];
	Weapon weapon1;
	Weapon weapon2;
	Weapon weapon3;
	int armor;
	int shield;
	int speed;
	int hitpoints;
} Robot;

void gunAssemble(Weapon* wp, int model){
	switch(model){
		case turbolaser:
			wp->range = 4;
			wp->splashDamage = 50;
			wp->blastDamage = 50;
			wp->firerate = 1;
			wp->critChance = 0.2;
			wp->accuracy = 0.75;
		break;
		case plasmagun:
			wp->range = 2;
			wp->splashDamage = 70;
			wp->blastDamage = 100;
			wp->firerate = 1;
			wp->critChance = 0.4;
			wp->accuracy = 0.67;
		break;
		case bolter:
			wp->range = 3;
			wp->splashDamage = 25;
			wp->blastDamage = 10;
			wp->firerate = 4;
			wp->critChance = 0.1;
			wp->accuracy = 0.5;
		break;
		case rocketpod:
			wp->range = -4;
			wp->splashDamage = 50;
			wp->blastDamage = 15;
			wp->firerate = 2;
			wp->critChance = 0.3;
			wp->accuracy = 0.67;
		break;
		case powerfist:
			wp->range = 0;
			wp->splashDamage = 50;
			wp->blastDamage = 50;
			wp->firerate = 1;
			wp->critChance = 0.5;
			wp->accuracy = 1.0;
		break;
		case powerclaw:
			wp->range = 0;
			wp->splashDamage = 30;
			wp->blastDamage = 10;
			wp->firerate = 2;
			wp->critChance = 0.5;
			wp->accuracy = 1.0;
		break;
		case inferno:
			wp->range = 1;
			wp->splashDamage = 15;
			wp->blastDamage = 10;
			wp->firerate = 3;
			wp->critChance = 0.1;
			wp->accuracy = 1.0;
		break;
		case predator:
			wp->range = -4;
			wp->splashDamage = 30;
			wp->blastDamage = 25;
			wp->firerate = 1;
			wp->critChance = 0.3;
			wp->accuracy = 1.0;
		break;
		case shredder:
			wp->range = 0;
			wp->splashDamage = 10;
			wp->blastDamage = 1;
			wp->firerate = 4;
			wp->critChance = 0.5;
			wp->accuracy = 1.0;
		break;
		case defiler:
			wp->range = 4;
			wp->splashDamage = 30;
			wp->blastDamage = 15;
			wp->firerate = 2;
			wp->critChance = 0.2;
			wp->accuracy = 0.75;
		break;
		case volcano:
			wp->range = 3;
			wp->splashDamage = 75;
			wp->blastDamage = 75;
			wp->firerate = 1;
			wp->critChance = 0;
			wp->accuracy = 1.0;
		break;
		case none:
			wp->range = 0;
			wp->splashDamage = 0;
			wp->blastDamage = 0;
			wp->firerate = 0;
			wp->critChance = 0;
			wp->accuracy = 0;
		break;
	}
}

void output(char *string, int x1, int x2, int y1, int y2){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
	COORD pos;
	for(pos.Y = y1; pos.Y < y2; pos.Y++){ 
		for(pos.X = x1; pos.X < x2; pos.X++){ 
			if(pos.X == x1 || pos.X == x2-1 || pos.Y == y1 || pos.Y == y2-1){
				SetConsoleCursorPosition(hConsole, pos);
				printf("*");
			}
			else{
				SetConsoleCursorPosition(hConsole, pos); 
				printf(" "); 
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

void input(char *string, int x1, int x2, int y1, int y2){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
	COORD pos;
	for(pos.Y = y1; pos.Y < y2; pos.Y++){ 
		for(pos.X = x1; pos.X < x2; pos.X++){ 
			if(pos.X == x1 || pos.X == x2-1 || pos.Y == y1 || pos.Y == y2 - 1){
				SetConsoleCursorPosition(hConsole, pos);
				printf("*");
			}
			else{
				SetConsoleCursorPosition(hConsole, pos); 
				printf(" "); 
			}
		} 
	} 
	pos.X = x1 + 2;
	pos.Y = y1 + 2;
	SetConsoleCursorPosition(hConsole, pos);
	gets(string);
	if(strlen(string)>20){
		system("cls");
		output("Too long. Try again", 19, 60, 4, 20);
		system("cls");
		input(string, x1, x2, y1, y2);
	}
}

int checkName(char *string){
	FILE *fp;
	char tmp[100];
	sprintf(tmp, "%s.txt", string);
	if((fp = fopen(tmp, "r")) == NULL)
		return 0;
	fclose(fp);
	return 1;
}

void botAssemble(Robot* bot, int pattern, Weapon* wp1, Weapon* wp2, Weapon* wp3){
	char *botname = malloc(20);
	do{
		system("cls");
		output("input your bot name", 19, 60, 4, 20);
		Sleep(2000);
		system("cls");
		input(botname, 19, 60, 4, 20);
	}while(checkName(botname));
	strcpy(bot->name, botname);
	bot->weapon1 = *wp1;
	bot->weapon2 = *wp2;
	bot->weapon3 = *wp3;
	switch(pattern){
		case lucius:
			bot->speed = 3;
			bot->armor = 30;
			bot->shield = 45;
			bot->hitpoints = 250;
		break;
		case contemptor:
			bot->speed = 1;
			bot->armor = 35;
			bot->shield = 30;
			bot->hitpoints = 300;
		break;
		case mars:
			bot->speed = 2;
			bot->armor = 35;
			bot->shield = 28;
			bot->hitpoints = 220;
		break;
		case phobos:
			bot->speed = 4;
			bot->armor = 35;
			bot->shield = 22;
			bot->hitpoints = 250;
		break;
		case graia:
			bot->speed = 2;
			bot->armor = 40;
			bot->shield = 40;
			bot->hitpoints = 300;
		break;
	}
	free(botname);
}

char *formGunStats(Weapon wp, char *string, int WNumber){
	if(wp.blastDamage == 0){
		string = " ";
		return string;
	}
	sprintf(string, "WEAPON %d:\nRange\t%d\nSplash damage\t%d\nBlast Damage\t%d\nFirerate\t%d\nCrit Chance\t%lf\nAccuracy\t%lf\%", WNumber, wp.range, wp.splashDamage, wp.blastDamage, wp.firerate, wp.critChance, wp.accuracy * 100);
	return string;
}

char *formBotStats(Robot *bot, char *string){
	char *tmp1 = malloc(100);
	char *tmp2 = malloc(100);
	char *tmp3 = malloc(100);
	sprintf(string, "%s\n%s\n%s\nROBOT:\nArmor:\t%d\nShield:\t%d\nSpeed:\t%d\nHitpoints:\t%d", formGunStats(bot->weapon1, tmp1, 1), formGunStats(bot->weapon2, tmp2, 2), formGunStats(bot->weapon3, tmp3, 3),
	bot->armor, bot->shield, bot->speed, bot->hitpoints);
	return string;
}