#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int GetFileSize(FILE* file)
{
	if(file == NULL) return -1;
    fseek(file, 0L, SEEK_END); 
    size_t res = ftell(file);
    fseek(file, 0, SEEK_SET);
    return res;
}


int Split(char* string, char* delim, char** splittedString ) {
    int i = 0;
    splittedString[0] = strtok(string, delim);
    while(splittedString[i] != NULL) 
	{
		i++;
        splittedString[i] = strtok(NULL, delim);
    }
    return i;
} 

int main()
{
	FILE *stringFile, *delimFile;
	stringFile = fopen("string.txt", "r");
	delimFile = fopen("delim.txt", "r");
	int stringSize = GetFileSize(stringFile);
	int delimSize = GetFileSize(delimFile);
	char* string = (char*)calloc(stringSize + 1, sizeof(char));
	char* delim = (char*)calloc(delimSize + 1, sizeof(char));
    fgets(string, stringSize, stringFile);
    fgets(delim, delimSize, delimFile);
	
	char** splittedString = (char**)calloc(stringSize+1, sizeof(char));
	int wordsNumber = Split(string, delim, splittedString);
	
	printf("%d\n", wordsNumber);
	
	for (int i = 0; i < wordsNumber; i++) 
	{
        printf("[%u]: %s\n", i + 1, splittedString[i]);
    }
	
	fclose(stringFile);
	fclose(delimFile);
	
	free(string);
	free(delim);
	free(splittedString);
	
	return 0;
}
