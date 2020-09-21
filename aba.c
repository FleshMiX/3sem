#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void AbaGenerate(char* string, int n)
{
    char currentLetter = 'A';

    for(int i = 0; i < n; i++) {
	int len = strlen(string);
	string[len] = currentLetter;
	// strncpy(string + len + 1, string, i);
	for(int j = 0; j < len; j++)
	    string[len + j + 1] = string[len - j - 1];
	currentLetter++;
    }
}

int main(int argc, char** argv)
{
    int n;
    scanf("%d", &n);
    char* result = (char*)calloc(pow(2, n) - 1, 1);
    AbaGenerate(result, n);
    printf("%s\n", result);
    free(result);
}
