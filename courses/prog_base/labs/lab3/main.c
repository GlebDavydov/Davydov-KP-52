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
		getch();
		return 0;
	}
	if(0){
N1:
		readString(defaultString);
	}
	if(checkForDouble(defaultString)){
		goto N1;
		}
	outputAsResult(defaultString);
	outputAsHelp("type 'help' for list of commands");
	char command[80];
	int a;
	while(1){
		a = readAsCommand(command);
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
					outputAsHelp("Input new string");
					check = readString(defaultString);
					if(check == 0){
						outputAsHelp("Sorry, too long");
						getch();
						return 0;
					}
					outputAsResult(defaultString);
					if(checkForDouble(defaultString))
						goto N2;
					if(0){
						N2:
						readString(defaultString);
					}
					outputAsHelp("delete \nreplace \nreplace and flop \nlist of words \nnumber of words \nlongest word \nstring length \nstring comparison \nletter number \nclear waste \nexit");
					break;
				}
			case xchange:{
					char new[80];
					outputAsHelp("Input new string");
					check = readString(new);
					if(check == 0){
						outputAsHelp("Sorry, too long");
						return 0;
					}
					xchangeString(new, defaultString);
					outputAsResult(defaultString);
					if(checkForDouble(defaultString))
						goto N3;
					if(0){
						N3:
						readString(defaultString);
					}
					outputAsHelp("delete \nreplace \nreplace and flop \nlist of words \nnumber of words \nlongest word \nstring length \nstring comparison \nletter number \nclear waste \nexit");
					break;
				}
			case words:{
					char result[80];
					wordOutput(defaultString, result);
					outputAsResult(result);
					getch();
					outputAsResult(defaultString);
					break;
				}
			case wordnumber:{
				int result = wordAmount(defaultString);
				char tmp[80];
				sprintf(tmp, "String contains %d words", result);
				outputAsResult(tmp);
				getch();
				outputAsResult(defaultString);
				break;
				}
			case maxword:{
				char result[80];
				int lnght = longestWord(defaultString, result);
				if(lnght == 0)
					break;
				char output[80];
				sprintf(output, "longest word is '%s' and has %d letters", result, lnght);
				outputAsResult(output);
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
					char tok[80];
					outputAsHelp("Input the sub string");
					check = readString(tok);
					if(check == 0){
						outputAsHelp("Sorry, too long");
						return 0;
					}
					int result = strAus(defaultString, tok);
					char *res2;
					sprintf(res2, "this string is met %d times", result);
					outputAsResult(res2);
					getch();
					outputAsResult(defaultString);
					outputAsHelp("delete \nreplace \nreplace and flop \nlist of words \nnumber of words \nlongest word \nstring length \nstring comparison \nletter number \nclear waste \nexit");
					break;
				}
			case letters:{
					int ln = letterNumber(defaultString);
					char result[80];
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