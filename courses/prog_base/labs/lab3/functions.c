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
	if(strcmp(string, "help"))
		return help;
	else if(strcmp(string, "exit"))
		return blowup;
	else if(strcmp(string, "delete"))
		return delete;
	else if(strcmp(string, "replace"))
		return change;
	else if(strcmp(string, "replace and flop"))
		return xchange;
	else if(strcmp(string, "list of words"))
		return words;
	else if(strcmp(string, "number of words"))
		return wordnumber;
	else if(strcmp(string, "longest word"))
		return maxword;
	else if(strcmp (string, "string length"))
		return strsize;
	else if(strcmp (string, "string comparison"))
		return straus;
	else if(strcmp (string, "letter number"))
		return letters;
	else if(strcmp(string, "clear waste"))
		return shorten;
	else if(strcmp(string, "fuck you") || strcmp(string, "fuckyou") || strcmp(string, "FUCK YOU") || strcmp(string, "FUCK U") || strcmp(string, "FUCKYOU") || strcmp(string, "fuck u"))
		return fuck;
	else 
		return incorrect;
}

int checkForDouble(const char *string){
	int counter = 0;
	int arr[strlen(string)];
	int i;
	for(i=0; isdigit(string[i]) || string[i] == '.' ; i++){
		if(isdigit(string[i]))
			arr[i] = string[i];
		else{
			counter = i;
			arr[i] = 0;
		}
	}
	i++;
	if(string[i] != '\n' && string[i] != '\0' || counter == 0)
		return 0;
	else {
			double res = 0;
			int power;
			for(int j=0; j < i; j++){
				res += arr[j] * pow(10, counter - (1+j));
			}
			outputAsHelp("You have input a real number. Give me its power!");
			scanf("%f", &power);
			res = pow(res, power);
			char *result;
			sprintf(result, "%lf", &res);
			outputAsResult(result);
			outputAsHelp("Input new starting string");
		return 1;
	}
}

void deleteString(char *string){
	string = NULL;
	outputAsResult(" ");
}

void xchangeString(char *string, char *result){
	char tmp;
	for(int i = 0; i <= strlen(string)/2; i++){
		tmp = string[i];
		string[i] = string[(strlen(string)/2) - i];
		string[(strlen(string)/2) - i] = tmp;
	}
	strcpy(result, string);
	string = NULL;
}

void wordOutput(const char *string, char *result){
	char *p;
	strcpy(p, string);
	p = strtok(p, " \n\r\t");
	sprintf(result, "'%c'", p);
	while(p != NULL){
		p = strtok(NULL, " ");
		sprintf(result, "%c,'%c'", result, p);
	}
}

int wordAmount(const char * string){
	char* p;
	int wA = 0;
	strcpy(p, string);
	p = strtok(p, " \r\t");
	if(p != 0)
		wA++;
	else
		return 0;
	while(p!= NULL){
		wA++;
		p = strtok(NULL, " \r\t");
	}
	return wA;
}

int longestWord(const char * string, char * resWord){
	char *p;
	strcpy(p, string);
	int wLen;
	int wMaxLen;
	p = strtok(p, " \r\t");
	if(p == NULL){
		sprintf(resWord, "Error reading your message");
		outputAsHelp(resWord);
		return 0;
	}
	wMaxLen = strlen(p);
	strcpy(resWord, p);
	while(p!=NULL){
		p = strtok(NULL, " \r\t");
		wLen = strlen(p);
		if(wLen >= wMaxLen){
			wMaxLen = wLen;
			strcpy(resWord, p);
		}
	}
	return wMaxLen;
}

int strAus(const char * string, const char * interjection){
	char *p;
	strcpy(p, string);
	int a = 0;
	p = strtok(p, interjection);
	if(p == NULL)
		return 0;
	a++;
	while(p != NULL){
		a++;
		p = strtok(NULL, interjection);
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

void oddClean(char *string){
	for(int i = 0; string[i] != '\n'; i++){
		if(string[i] == ' '){
			while(string[i+1] == ' '){
				int j;
				char tmp;
				for(j = i+1; string[j] == '\n'; j++){
					string[j] = string[j+1];
				}
				string[j+1] = '\0';
			}
		}
	}
}