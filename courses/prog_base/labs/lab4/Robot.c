#include'functions.c'

enum weapons{turbolaser = 1, plasmagun, bolter, rocketpod, powerfist, powerclaw, inferno, predator, shredder, defiler, volcano};
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
	int plating;
	int shield;
	int speed;
	int hitpoints;
} Robot;

*Robot robotConstructor(void){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	char comm;
	int cursor = 0;
	char *str1 = "Choose the robot pattern";
	char *str2 = "lucius";
	char *str3 = "contemptor";
	char *str4 = "mars";
	char *str5 = "phobos";
	char *str6 = "graia"
	char *menu = malloc(1024);
	sprintf(menu, "%s \n%s \n%s \n%s \n%s \n%s", str1, str2, str3, str4, str5, str6);
	int pattern = 0;
	while(pattern == 0){
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
			case 4:
				puts(str6);
				break;
			default:
				break;
		}
		comm = getch();
		switch((int)comm){
			case 27: //escape
				return 0;
			case 13: //enter
				switch(cursor){
					case 0:
						pattern = lucius;
						break;
					case 1:
						pattern = contemptor;
						break;
					case 2:
						pattern = mars;
						break;
					case 3:
						pattern = phobos;
						break;
					case 4:
						pattern = graia;
						break;
					default:
						break;
				}
				break;
			case 80: //down key
				if(pos.Y > 6)
					cursor--;
				break;
			case 72: //up key
				if(pos.Y < 10)
					cursor++;
				break;
			default:
				break;
		}
		if(pattern != 0){
			switch(pattern){
				case lucius:
					outputAsHelp("lucius pattern robot is most universal one with superior shields and good speed\nWeapon slots: 2\nSpeed: 3\nArmor: 30\nShields: 45\nHitpoints: 250");
					break;
				case contemptor:
					outputAsHelp("contemptor pattern robot shows its best as a long-range fire support\nWeapon slots: 3\nSpeed: 1\nArmor: 35\nShields: 30\nHitpoints: 300");
					break;
				case mars:
					outputAsHelp("mars pattern robot is a middle-distance powerful combat robot\nWeapon slots: 3\nSpeed: 2\nArmor: 35\nShields: 28\nHitpoints: 220");
					break;
				case phobos:
					outputAsHelp("phobos pattern robot is a fast and agile close-combat machine\nWeapon slots: 2\nSpeed: 4\nArmor: 35\nShields: 22\nHitpoints: 230");
					break;
				case graia:
					outputAsHelp("graia pattern robot is big, mean and very tough\nWeapon slots: 2\nSpeed: 2\nArmor: 40\nShields: 40\nHitpoints: 300");
					break;
			}
			char *apStr1 = "Apply";
			char *apStr2 = "Return";
			int status = 0;
			cursor = 0;
			char a;
			while(status == 0){
				switch(cursor){
					case 0:
						fmt = BACKGROUND_GREEN | BACKGROUND_RED;
						setConsoleTextAttribute(hConsole, fmt);
						pos.Y = 12;
						pos.X = 0;
						setConsoleCursorPosition(hConsole, pos);
						puts(apStr1);
						fmt = BACKGROUND_BLUE | BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_GREEN;
						setConsoleTextAttribute(hConsole, fmt);
						pos.Y = 13;
						pos.X = 0;
						setConsoleCursorPosition(hConsole, pos);
						puts(apStr2);
						break;
					case 1:
						fmt = BACKGROUND_GREEN | BACKGROUND_RED;
						setConsoleTextAttribute(hConsole, fmt);
						pos.Y = 13;
						pos.X = 0;
						setConsoleCursorPosition(hConsole, pos);
						puts(apStr2);
						fmt = BACKGROUND_BLUE | BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_GREEN;
						setConsoleTextAttribute(hConsole, fmt);
						pos.Y = 12;
						pos.X = 0;
						setConsoleCursorPosition(hConsole, pos);
						puts(apStr1);
						break;
				}
				a = getch();
				switch((int)a){
					case 80:
					case 72:
						cursor = (cursor+1)%2;
						break;
					case 13:
						status = 1;
						if(cursor)
							pattern = 0;
						break;
					default:
						break;
				}
			}
		}
	}
	*Robot newBot = malloc(sizeof(Robot));
	char botname[30];
	outputAsHelp("Input a name for your robot. It is saved forever and may not be changed.");
	readStr(botname);
	checkName(botname);
	int guns = 0;
	cursor = 0;
	Weapon wp1;
	*str1 = "Choose the first weapon";
	*str2 = "turbolaser";
	*str3 = "plasmagun";
	*str4 = "bolter";
	*str5 = "rocketpod";
	*str6 = "powerfist";
	char *str7 = "powerclaw";
	char *str8 = "inferno";
	char *str9 = "predator missile";
	char *str10 = "shredder";
	char *str11 = "defiler cannon";
	char *str12 = "volcano blaster";
	sprintf(menu, "%s \n%s \n%s \n%s \n%s \n%s \n%s \n%s \n%s \n%s \n%s \n%s", str1, str2, str3, str4, str5, str6, str7, str8, str9, str10, str11, str12);
	while(guns == 0){
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
			case 4:
				puts(str6);
				break;
			case 5:
				puts(str7);
				break;
			case 6:
				puts(str8);
				break;
			case 7:
				puts(str9);
				break;
			case 8:
				puts(str10);
				break;
			case 9:
				puts(str11);
				break;
			case 10:
				puts(str12);
				break;
			default:
				break;
		}
		comm = getch();
		switch((int)comm){
			case 27: //escape
				return 0;
			case 13: //enter
				switch(cursor){
					case 0:
						guns = turbolaser;
						break;
					case 1:
						guns = plasmagun;
						break;
					case 2:
						guns = bolter;
						break;
					case 3:
						guns = rocketpod;
						break;
					case 4:
						guns = powerfist;
						break;
					case 5:
						guns = powerclaw;
						break;
					case 6:
						guns = inferno;
						break;
					case 7:
						guns = predator;
						break;
					case 9:
						guns = shredder;
						break;
					case 10:
						guns = defiler;
						break;
					case 11:
						guns = volcano;
						break;
					default:
						break;
				}
				break;
			case 80: //down key
				if(pos.Y > 6)
					cursor--;
				break;
			case 72: //up key
				if(pos.Y < 10)
					cursor++;
				break;
			default:
				break;
		}
		if(guns != 0){
			switch(guns){
				case turbolaser:
					outputAsHelp("turbolaser is a reliable long range gun\nRange: 4*\nSplash damage: 50\nBlast damage: 50\nFirerate: 1\nCritical hit chance: 0,2\nAccuracy: 75%\n*range below zero means the weapon can't be used in close combat");
					break;
				case plasmagun:
					outputAsHelp("turbolaser is a reliable long range gun\nRange: 4*\nSplash damage: 50\nBlast damage: 50\nFirerate: 1\nCritical hit chance: 0,2\nAccuracy: 75%\n*range below zero means the weapon can't be used in close combat");
					break;
				case bolter:
					outputAsHelp("turbolaser is a reliable long range gun\nRange: 4*\nSplash damage: 50\nBlast damage: 50\nFirerate: 1\nCritical hit chance: 0,2\nAccuracy: 75%\n*range below zero means the weapon can't be used in close combat");
					break;
				case rocketpod:
					outputAsHelp("turbolaser is a reliable long range gun\nRange: 4*\nSplash damage: 50\nBlast damage: 50\nFirerate: 1\nCritical hit chance: 0,2\nAccuracy: 75%\n*range below zero means the weapon can't be used in close combat");
					break;
				case powerfist:
					outputAsHelp("turbolaser is a reliable long range gun\nRange: 4*\nSplash damage: 50\nBlast damage: 50\nFirerate: 1\nCritical hit chance: 0,2\nAccuracy: 75%\n*range below zero means the weapon can't be used in close combat");
					break;
			}
			char *apStr1 = "Apply";
			char *apStr2 = "Return";
			int status = 0;
			cursor = 0;
			char a;
			while(status == 0){
				switch(cursor){
					case 0:
						fmt = BACKGROUND_GREEN | BACKGROUND_RED;
						setConsoleTextAttribute(hConsole, fmt);
						pos.Y = 14;
						pos.X = 0;
						setConsoleCursorPosition(hConsole, pos);
						puts(apStr1);
						fmt = BACKGROUND_BLUE | BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_GREEN;
						setConsoleTextAttribute(hConsole, fmt);
						pos.Y = 15;
						pos.X = 0;
						setConsoleCursorPosition(hConsole, pos);
						puts(apStr2);
						break;
					case 1:
						fmt = BACKGROUND_GREEN | BACKGROUND_RED;
						setConsoleTextAttribute(hConsole, fmt);
						pos.Y = 15;
						pos.X = 0;
						setConsoleCursorPosition(hConsole, pos);
						puts(apStr2);
						fmt = BACKGROUND_BLUE | BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_GREEN;
						setConsoleTextAttribute(hConsole, fmt);
						pos.Y = 14;
						pos.X = 0;
						setConsoleCursorPosition(hConsole, pos);
						puts(apStr1);
						break;
				}
				a = getch();
				switch((int)a){
					case 80:
					case 72:
						cursor = (cursor+1)%2;
						break;
					case 13:
						status = 1;
						if(cursor)
							pattern = 0;
						break;
					default:
						break;
				}
			}
		}
}