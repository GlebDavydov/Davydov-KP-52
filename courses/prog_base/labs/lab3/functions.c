#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<conio.h>
#include<math.h>

void startConsole(){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = 0;
	pos.Y = 14;
	for(;pos.X < 80; pos.X++){
		SetConsoleCursorPosition(hConsole, pos);
		printf("_");
	}
	pos.X = 0;
	pos.Y = 1;
	SetConsoleCursorPosition(hConsole, pos);
	puts("Welcome! Input your string to begin");
}

void outputAsResult(const char *string){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.Y = 15;
	for(pos.X = 0; pos.X <= 79; pos.X++){
		SetConsoleCursorPosition(hConsole, pos);
		puts(" ");
	}
	pos.X = 0;
	pos.Y = 15;
	SetConsoleCursorPosition(hConsole, pos);
	int background_color = BACKGROUND_GREEN | BACKGROUND_RED;
	int fmt = background_color | BACKGROUND_INTENSITY;
	SetConsoleTextAttribute(hConsole, fmt);
	printf(string);
	fmt = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE;
	SetConsoleTextAttribute(hConsole, fmt);
}

void outputAsHelp(const char *string){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	for(pos.Y = 1; pos.Y < 13; pos.Y++){
		for(pos.X = 0; pos.X <= 79; pos.X++){
			SetConsoleCursorPosition(hConsole, pos);
			puts(" ");
		}
	}
	int background_color = BACKGROUND_GREEN;
	int fmt = background_color | BACKGROUND_INTENSITY;
	SetConsoleTextAttribute(hConsole, fmt);
	pos.X = 0;
	pos.Y = 1;
	SetConsoleCursorPosition(hConsole, pos);
	printf(string);
	fmt = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE;
	SetConsoleTextAttribute(hConsole, fmt);
}

int readString(char *string){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.Y = 0;
	for(pos.X = 0; pos.X <= 79; pos.X++){
		SetConsoleCursorPosition(hConsole, pos);
		puts(" ");
	}
	pos.Y = 0;
	pos.X = 0;
	SetConsoleCursorPosition(hConsole, pos);
	fgets(string, 81, stdin);
	int size = strlen(string);
	if(size >= 80)
		return 0;
	return size;
}

int readAsCommand(char *string){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.Y = 0;
	for(pos.X = 0; pos.X <= 79; pos.X++){
		SetConsoleCursorPosition(hConsole, pos);
		puts(" ");
	}
	pos.Y = 0;
	pos.X = 0;
	SetConsoleCursorPosition(hConsole, pos);
	fgets(string, 80, stdin);
	enum commands {help, blowup, delete, change, xchange, words, wordnumber, maxword, strsize, straus, letters, shorten, incorrect, fuck};
	if(!strcmp(string, "help\n"))
		return help;
	else if(!strcmp(string, "exit\n"))
		return blowup;
	else if(!strcmp(string, "delete\n"))
		return delete;
	else if(!strcmp(string, "replace\n"))
		return change;
	else if(!strcmp(string, "replace and flop\n"))
		return xchange;
	else if(!strcmp(string, "list of words\n"))
		return words;
	else if(!strcmp(string, "number of words\n"))
		return wordnumber;
	else if(!strcmp(string, "longest word\n"))
		return maxword;
	else if(!strcmp (string, "string length\n"))
		return strsize;
	else if(!strcmp (string, "string comparison\n"))
		return straus;
	else if(!strcmp (string, "letter number\n"))
		return letters;
	else if(!strcmp(string, "clear waste\n"))
		return shorten;
	else if(!strcmp(string, "fuck you\n") || !strcmp(string, "fuckyou\n") || !strcmp(string, "FUCK YOU\n") || !strcmp(string, "FUCK U\n") || !strcmp(string, "FUCKYOU\n") || !strcmp(string, "fuck u\n"))
		return fuck;
	else 
		return incorrect;
}

int checkForDouble(const char *string){
	int counter = 0;
	int arr[strlen(string)];
	int i;
	for(i=0; isdigit(string[i]) || string[i] == '.'; i++){
		if(isdigit(string[i])){
			switch(string[i]){
			case 48:
				arr[i] = 0;
				break;
			case 49:
				arr[i] = 1;
				break;
			case 50:
				arr[i] = 2;
				break;
			case 51:
				arr[i] = 3;
				break;
			case 52:
				arr[i] = 4;
				break;
			case 53:
				arr[i] = 5;
				break;
			case 54:
				arr[i] = 6;
				break;
			case 55:
				arr[i] = 7;
				break;
			case 56:
				arr[i] = 8;
				break;
			case 57:
				arr[i] = 9;
				break;
			}
		}
		else{
			if(counter != 0)
				return 0;
			counter = i;
			arr[i] = 0;
		}
	}
	if((string[i] != '\n' && string[i] != '\0') || counter == 0)
		return 0;
	else {
			double res = 0;
			int power;
			for(int j=0; j < i; j++){
				if(j < counter)
					res += arr[j] * pow(10, counter - (1+j));
				else
					res += arr[j] * pow(10, counter - j);
			}
			getch();
			outputAsHelp("You have input a real number. Input the power for calculation");
			char tmp[80];
			readString(tmp);
			sscanf(tmp, "%d", &power);
			res = pow(res, power);
			char *result;
			sprintf(result, "%lf", res);
			outputAsResult(result);
			outputAsHelp("Input new starting string");
		return 1;
	}
}

void deleteString(char *string){
	string = NULL;
	outputAsResult(NULL);
}

void xchangeString(char *string, char *result){
	char tmp;
	for(int i = 0; i < (strlen(string)/2); i++){
		tmp = string[i];
		string[i] = string[strlen(string) - (2 + i)];
		string[strlen(string) - (2+i)] = tmp;
	}
	strcpy(result, string);
	string = NULL;
}


void oddClean(char *string){
	for(int i = 0; string[i] != '\n'; i++){
		if(string[i] == ' ' || string[i] == '\r' || string[i] == '\t'){
			if(string[i] != ' ')
				string[i] = ' ';
			while(string[i+1] == ' ' || string[i+1] == '\r' || string[i+1] == '\t'){
				int j;
				for(j = i+1; string[j] != '\n'; j++){
					string[j] = string[j+1];
				}
				string[j+1] = '\0';
			}
		}
	}
}

int wordAmount(const char * string){
	char p[strlen(string)];
	int wA = 0;
	strcpy(p, string);
	oddClean(p);
	for(int i = 0; p[i] != '\n'; i++){
		if(p[i] == ' ')
			wA++;
	}
	return wA;
}

void wordOutput(char *string, char *result){
	char temp[80];
	char *p = &temp[0];
	strcpy(p, string);
	oddClean(p);
	p = strtok(p, " ");
	sprintf(result, "%s", p);
	while(p != NULL){
		p = strtok(NULL, " ");
		if(p != NULL)
			sprintf(result, "%s,%s", result, p);
	}
}

int longestWord(char * string, char * resWord){
	char temp[80];
	char *p = &temp[0];
	strcpy(p, string);
	oddClean(p);
	int wLen;
	int wMaxLen;
	p = strtok(p, " ");
	if(p == NULL){
		sprintf(resWord, "Error reading your message");
		outputAsHelp(resWord);
		return 0;
	}
	wMaxLen = strlen(p);
	strcpy(resWord, p);
	while(p!=NULL){
		p = strtok(NULL, " \r\t");
		if(p != NULL){
			wLen = strlen(p);
			if(wLen >= wMaxLen){
				wMaxLen = wLen;
				strcpy(resWord, p);
			}
		}
	}
	return wMaxLen;
}

int strAus(const char * string, const char * pfind){
	char *p;
	int a = 0;
	p = strstr(string, pfind);
	while(p != NULL){
		a++;
		p = strstr(p+(strlen(pfind)), pfind);
	}
	return a;
}

int letterNumber(const char * string){
	int res = 0;
	for(int i = 0; string[i] != '\n' && string[i] != '\0'; i++){
		if(isalpha(string[i]))
			res++;
	}
	return res;
}