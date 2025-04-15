//HW 12 Gabriel Cotua
#include <stdio.h>
#include <string.h>

#define SIZE 41 // size of the input character array
#define MAXMATCHES 10 // max matches
#define FLUSH while(getchar() != '\n');


int CharIsAt( char pStr[], const char ch, int loc[], int mLoc);
void resetMatches(int matches[], int * piMatches, int * piMatchesEnd);
int myStrCh( const char goal, char pStr[] );

int main(void) {
	printf("\n\n|#####################|\n|HW #12, Gabriel Cotua|\n|#####################|\n\n");


	char userInput[SIZE], lookUp;
	char *piUserInput = userInput, *piUserInputEnd = userInput + SIZE; // char pointers
	int matches[MAXMATCHES], counter = 0;
	int *piMatches = matches, *piMatchesEnd = matches + MAXMATCHES; // int pointers

	while ( printf("Enter a line of text:\n"), fgets(userInput, SIZE, stdin) && userInput[0] != '\n') {

		// cleaning \n character
		if (myStrCh('\n', userInput) == 1) {
		    FLUSH;
		}

		resetMatches( matches, piMatches, piMatchesEnd); // reseting the array of matches
		userInput[strlen(userInput)-1] = '\0'; // setting an ending point
		printf("Your Input: %s\n", userInput);
		printf("Input a character to look for: ");
		lookUp = getchar();

		// make sure user doesn't look for a '\n'
        while (lookUp == '\n') {
            printf("Input a character to look for: ");
            lookUp = getchar();
        }
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

		printf("The character '%c' was found %d time(s).\n", lookUp, counter);
		printf("The first %d matches is/are at:", counter = ( (10 >= counter) ? counter:10) );
		// since counter isn't used in the code after, I changed the value to 10 as the maximum.

		// goes through the whole array looking for the matching values
		for ( piMatches = matches; piMatches < piMatchesEnd; piMatches++)
		{
			if(*piMatches != -1) {
				printf(" [%d]", *piMatches);
			}
		}
		printf(" in the string\n");
		printf("\"%s\"\n ", userInput);

		// using user input length, we are going to get all the locations of occurrences
		for (piUserInput = userInput, piMatches = matches; piUserInput < piUserInputEnd; piUserInput++)
		{
			if(*piMatches != -1 && *piMatches == piUserInput - userInput) {
				putchar('^');
				piMatches++;
			}
			else {
				putchar(' ');
			}
		}
		putchar('\n');
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

	for (char * piStr = pStr, * pEnd = piStr + strlen(pStr); piStr < pEnd; piStr++) {

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

void resetMatches(int matches[], int * piMatches, int * piMatchesEnd) {
    // starting array
	for ( piMatches = matches; piMatches < piMatchesEnd; piMatches++)
		*piMatches = -1;
}


// @param goal is the char you want to find
// @param pStr[] array of character that you want to check
// return 1 once the first match was found, return 0 otherwise
int myStrCh( const char goal, char pStr[] ){

    for(char * piStr = pStr, * piStrEnd = pStr + strlen(pStr); piStr < piStrEnd; piStr++ ){
        if (*piStr == goal) {
            return 1;
        }
    }

    return 0;
}
