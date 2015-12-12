#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int initFile(char *filename1, char *filename2, FILE *fp1, FILE *fp2);

void sortString(const char * sSource, char * sRes);

void sortFiles(FILE *fp1, FILE *fp2);

int main(int argc, char *argv[]){
	if(argc != 3){
		printf("You are expected to input source and result file names.");
		return 0;
	}
	char *fname1 = argv[1];
	char *fname2 = argv[2];
	FILE *source, *result;
	if(initFile(fname1, fname2, source, result))
		return 0;
	sortFiles(source, result);
	fclose(source);
	fclose(result);
	return 0;
}

int initFile(char *filename1, char *filename2, FILE *fp1, FILE *fp2){
if ((fp1 = fopen(filename1, "r")) == NULL){
		printf("\n no such source file exist");
		return 1;
	}
	if((fp2 = fopen(filename2, "w")) == NULL){
		printf("\n no such result file exist");
		return 1;
	}
	return 0;
}

void sortString(const char *sSource, char *sRes){
	strcpy(sRes, sSource);
	char temp;
	for(int i = 0; sRes[i+1] != '\n' && sRes[i+1] != '\0'; i++){
		for(int j = i+1; sRes[j+2] != '\n' && sRes[j+2] != '\0'; j++){
			if((int)sRes[j+1] >= (int)sRes[j]){
				temp = sRes[j];
				sRes[j] = sRes[j+1];
				sRes[j+1] = temp;
			}
		}
	}
}

void sortFiles(FILE *fp1, FILE *fp2){
	char *str1 = malloc(1000);
	char *str2 = malloc(1000);
	fseek(fp2, 0, SEEK_SET);
	while(!feof(fp1)){
		fflush(fp1);
		fgets(str1, 999, fp1);
		fclose(fp1);
		sortString(str1, str2);
		fflush(fp1);
		fprintf(fp2, "%s\n", str2);
		fclose(fp2);
	}
	free(str1);
	free(str2);
}