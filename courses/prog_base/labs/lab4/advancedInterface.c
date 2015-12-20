#include"functs.c"

int battleMenu2(){
	char name1[20];
	char name2[20];
	system("cls");
	output("Player 1, input your name", 19, 60, 4, 20);
	Sleep(2000);
	system("cls");
	input(name1, 19, 60, 4, 20);
	system("cls");
	output("Player 2, input your name", 19, 60, 4, 20);
	Sleep(2000);
	system("cls");
	input(name2, 19, 60, 4, 20);
	while(!strcmp(name1, name2)){
		system("cls");
		output("Names shouldn't match", 19, 60, 4, 20);
		Sleep(2000);
		system("cls");
		input(name2, 19, 60, 4, 20);
	}
	char *commands[] = {"Quit", "Choose robot 1", "Choose robot 2", "START THE BATTLE!"};
	Robot *botRed = malloc(sizeof(Robot));
	Robot *botBlue = malloc(sizeof(Robot));
	int st1 = 0; 
	int st2 = 0;
	while(1){
		system("cls");
		char botname1[100];
		char botname2[100];
		if(st1)
			output(botname1, 59, 80, 0, 5);
		if(st2)
			output(botname2, 59, 80, 5, 10);
		int a = menu(commands, 4, " ", 1);
		if(!a)
			return 0;
		char tmp[100];
		switch(a){
			case 0:
				return 0;
			case 1:
					sprintf(tmp, "%s,\n input your Robot name", name1);
					system("cls");
					output(tmp, 19, 60, 4, 20);
					Sleep(2000);
					system("cls");
					input(botname1, 19, 60, 4, 20);
					loadBot(botRed, botname1);
					if(botRed != NULL)
						st1 = 1;
				break;
			case 2:
					sprintf(tmp, "%s,\n input your Robot name", name2);
					system("cls");
					output(tmp, 19, 60, 4, 20);
					Sleep(2000);
					system("cls");
					input(botname2, 19, 60, 4, 20);
					loadBot(botBlue, botname2);
					if(botBlue != NULL)
						st2 = 1;
				break;
				case 3:
					if(!st1 || !st2)
						break;
					startMultiBattle(botRed, botBlue, name1, name2);
				break;
		}
	}
	free(botRed);
	free(botBlue);
}

int menuMain(){
	enum comm{blowup, build, delete, FAQ, single, multi};
	char *commands[] = {"Quit", "Build a bot", "Delete a bot", "view FAQ", "Singleplayer", "Multiplayer"};
	char dName[20];
	while(1){
		switch(menu(commands, 6, "Use arrows to navigate", 0)){
		case blowup:
			system("cls");
			return 1;
		case build:
			robotConstructor();
			break;
		case delete:
			system("cls");
			input(dName, 19, 60, 4, 20);
			if(!deleteBot(dName)){
				system("cls");
				output("No such bot found", 19, 60, 4, 20);
				Sleep(2000);
			}
			break;
		case FAQ:
			instruction();
			break;
		//case single:
		case multi:
			battleMenu2();
			break;
		default:
			system("cls");
			return 1;
		}
	}
	system("cls");
	return 1;
}