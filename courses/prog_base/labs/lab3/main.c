#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#include"functions.c"

enum commands {help, blowup, delete, change, xchange, words, wordnumber, maxword, strsize, straus, letters, shorten, incorrect, fuck};

int main (void){
	char defaultString[80];
	startConsole();
	int check = readString(defaultString);
	if(check == 0){
		outputAsHelp("Sorry, too long");
		return 0;
	}
	while(checkForDouble(defaultString))
		readString(defaultString);
	outputAsResult(defaultString);
	outputAsHelp("type 'help' for list of commands");
	char command[80];
	int a;
	while(1){
		a = readAsCommand(command);
		char *tmp;
		sprintf(tmp, "%d", a);
		outputAsResult(tmp);
		switch(a){
			case help:{
					outputAsHelp("delete \nreplace \nreplace and flop \nlist of words \nnumber of words \nlongest word \nstring length \nstring comparison \nletter number \nclear waste \nexit");
					break;
				}
			case delete:{
					deleteString(defaultString);
					break;
				}
			case change:{
					deleteString(defaultString);
					readString(defaultString);
					outputAsResult(defaultString);
					while(checkForDouble(defaultString))
						readString(defaultString);
					break;
				}
			case xchange:{
					char new[80];
					readString(new);
					xchangeString(new, defaultString);
					outputAsResult(defaultString);
					while(checkForDouble(defaultString))
						readString(defaultString);
					break;
				}
			case words:{
					int lnght = (strlen(defaultString)) + (2 * wordAmount(defaultString));
					if(lnght > 80){
					outputAsHelp("sorry, too many words");
					break;
				}
					char *result;
					wordOutput(defaultString, result);
					outputAsResult(result);
					getch();
					outputAsResult(defaultString);
					break;
				}
			case wordnumber:{
				int result = wordAmount(defaultString);
				char * tmp;
				sprintf(tmp, "String contains %d words", result);
				outputAsResult(tmp);
				getch();
				outputAsResult(defaultString);
				break;
				}
			case maxword:{
				char *result;
				int lnght = longestWord(defaultString, result);
				if(lnght == 0)
					break;
				sprintf(result, "longest word is '%c' and has &d letters", result, lnght);
				outputAsResult(result);
				getch();
				outputAsResult(defaultString);
				break;
				}
			case strsize:{
					int result = strlen(defaultString);
					char *res2;
					sprintf(res2, "String length: %d", result);
					outputAsResult(res2);
					getch();
					outputAsResult(defaultString);
					break;
				}
			case straus:{
					char *tok;
					readString(tok);
					int result = strAus(defaultString, tok);
					char *res2;
					sprintf(res2, "this string is met %d times", result);
					outputAsResult(res2);
					getch();
					outputAsResult(defaultString);
					break;
				}
			case letters:{
					int ln = letterNumber(defaultString);
					char *result;
					sprintf(result, "String contains %d letters", ln);
					outputAsResult(result);
					getch();
					outputAsResult(defaultString);
					break;
				}
			case shorten:{
					oddClean(defaultString);
					outputAsResult(defaultString);
					break;
					}
			case fuck:{
					outputAsHelp("you've offenced me,\nI ain't gonna talk to you anymore\nP.S. wish you the same!");
					getch();
					return 0;
				}
			case incorrect:{
					outputAsHelp("incorrect command, type 'help' for list of commands");
					break;
			}
			case blowup:
				return 0;
			default:
				outputAsHelp("system error");
				return 0;
		}
	}
	getch();
	return 0;
}
