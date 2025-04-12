#include <stdio.h>
#include <stdlib.h>

#define SIZE 41 // size of the input character array
#define MAXMATCHES 10 // max matches
#define FLUSH while(getchar() != '\n')


int CharIsAt( char pStr[], const char ch, int loc[], int mLoc);

int main(void) {

	char userInput[SIZE], lookUp;
	char *piUserInput = userInput, *piUserInputEnd = userInput + SIZE; // char pointers
	int matches[MAXMATCHES], counter = 0;
	int *piMatches = matches, *piMatchesEnd = matches + MAXMATCHES; // int pointers
	
	// starting array
	for ( piMatches = matches; piMatches < piMatchesEnd; piMatches++) 
		*piMatches = -1;
	

	while ( printf("Enter a line of text:\n"), fgets(userInput, SIZE, stdin) && userInput[0] != '\n') {
		printf("Your Input: %s", userInput);
		printf("Input a character to look for: ");
		lookUp = getchar();
		FLUSH;

		counter = CharIsAt(userInput, lookUp, matches, MAXMATCHES);

		/*
		printf("Number of total matches: %d\n", counter);
		// cycling trough matches
		for (int * pi = matches, *piEnd = pi + MAXMATCHES; pi < piEnd; pi++)
		{
			printf("pointer found at: %d\n", *pi);
		}
		*/

		printf("The character \'%c\' was found %d\n", lookUp, counter);
		printf("The first 4 matches are at:");
		for ( piMatches = matches; piMatches < piMatchesEnd; piMatches++)
		{
			if(*piMatches != -1)
				printf(" %d", *piMatches);
		}
		printf(" in the string\n");
		printf("\"%s\"", userInput);
		for (piUserInput; piUserInput < piUserInputEnd; piUserInput++)
		{
			if(*piUserInput != -1)
				printf(" %d", *piUserInput);
			else
				putchar(" ");
		}
	}

    return 0;
}

/* 
@param pStr[] userInput String
@param ch character to look for
@param loc[] array where the index of the first matches will be save
@param mLoc size of loc[]
*/
int CharIsAt( char * pStr, const char ch, int * loc, int mLoc) {

	int * pLoc = loc, counter = 0;

	for (char * piStr = pStr, * pEnd = piStr + SIZE; piStr < pEnd; piStr++) {

		if (*piStr == ch ){
			if (pLoc - loc < mLoc) {
				*pLoc = piStr - pStr;
				pLoc++;
			}
			counter++;
		}
	}
	return counter;
}