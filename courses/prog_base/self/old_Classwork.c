#include<stdio.h>
#include<stdlib.h>
#include<string.h>


/*enum IntType {NOT_INT = 0, INT = 1, SHORT = 2, LONG = 4, LONG_LONG = 8};
typedef enum IntType IntType;

const char * getTypeName(IntType aType){
	switch (aType){
		case NOT_INT: return "Not an integer";
		case INT: return "Integer";
		case LONG: return "Long int";
		case SHORT: return "Short int";
		case LONG_LONG: return "Very long int";
		default: return "error";
	}
}

IntType getIntType(char *str){
	char * p = str;
	int counter = 0;
	int lC = 0, sC = 0, iC = 0;
	p = strtok(p, " \n\r\t");
	while(*p != NULL){
		counter++;
		if (strcmp(p, "int") == 0 && iC == 0){
			iC++;
		} else if (strcmp(p, "short") == 0 && sC == 0 && lC ==0 && iC <= 1){
			sC++;
		} else if (strcmp(p, "long")==0 && lC <= 1 && sC == 0 && iC <= 1){
			lC++;
		}
		else return NOT_INT;
		p = strtok(p, " \n\r\t");
	}
	if(counter < 1 || counter > 3)
		return NOT_INT;
	else if(lC == 1)
		return LONG;
	else if(lC == 2)
		return LONG_LONG;
	else if(sC == 1)
		return SHORT;
	else
		return INT;
}

char * trimStart(char * p){
	while(isspace(*p))
		p++;
	return p;
}

char * trimEnd(char * pstart){
	char * p = pstart + strlen(pstart) - 1;
	while(isspace(*p)&& p >= pstart)
		p--;
	p = p+1;
	*p = '\0';
	return(pstart);
}

char * trim(char * pstr){
	pstr = trimStart(trimEnd(pstr));
	return pstr;
}

int main(){
	char str[] = "long long int x;";
	char *pstr = NULL;
	pstr = trim(str);
	IntType t = getIntType(pstr);
	printf("Type is %s\n", getTypeName(t));
	return 0;
}*/

int main(void){
	//char *str = "kitty don't cry";
	char *fileName = "test.txt";
	char *mode = "w+";
	FILE *fp;
	double a;
	int b;
	fp = fopen(fileName, mode);
	if(NULL == fp){
		puts("error!");
		return 0;
	}
	//fprintf(fp, "%s\n%s\n%s", str, str, str, "%d", strlen(str));
	//puts("OK!");
	/*char str[80];
	fgets(str, 80, fp);
	while(!feof(fp)){
		puts(str);
		fgets(str, 80, fp);
	}*/
	fscanf(fp, "%lf", a);
	fscanf(fp, "%d", b);
	printf("%lf", a+b);
	fclose(fp);
	return 0;
}