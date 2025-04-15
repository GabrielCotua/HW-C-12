//HW 12 Gabriel Cotua
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 41 // size of the input character array
#define MAXMATCHES 10 // max matches
#define FLUSH while(getchar() != '\n');

int wordFound( char pStr[], char word[], int loc[], int mLoc);
int CharIsAt( char pStr[], const  char ch, int loc[], int mLoc);
void resetMatches(int matches[], int * piMatches, int * piMatchesEnd);
int myStrCh( const char goal, char pStr[] );

int main(void) {
	printf("\n\n|#####################|\n|HW #12, Gabriel Cotua|\n|#####################|\n\n");


	char lookUp;
	char userInput[SIZE], wordLookUp[11], *piUserInput = userInput, *piUserInputEnd = userInput + SIZE; // char pointers
	int counter = 0, ans = 0;
	int matches[MAXMATCHES], *piMatches = matches, *piMatchesEnd = matches + MAXMATCHES; // int pointers

	while ( printf("Want to look-up a word [0] or a letter [1]?: "), ans = getchar(), ans != 'n') {
        FLUSH;

        printf("%c", ans);
        switch (ans)
        {
            case ('0'):
            
                printf("Word!\n");
                printf("Enter a line of text:\n");
                fgets(userInput, SIZE, stdin);
                if (userInput[0] == '\n')
                    break;

                    // cleaning \n character
                if (myStrCh('\n', userInput) == 0) 
                        FLUSH;

                resetMatches( matches, piMatches, piMatchesEnd); // reseting the array of matches
                userInput[strlen(userInput)-1] = '\0'; // setting an ending point
                printf("Your Input: %s\n", userInput);
                printf("Input a word [max 10 characters] to look for: ");
                scanf("%10c", wordLookUp);

                // make sure user doesn't look for a '\n'
                while (wordLookUp[0] == '\n') {
                    printf("Input a word to look for: ");
                    scanf("%10c", wordLookUp);
                }
                FLUSH;

                counter = wordFound(userInput, wordLookUp, matches, MAXMATCHES);

                printf("The character '%s' was found %d time(s).\n", wordLookUp, counter);
                printf("The first %d matches is/are at:", counter = ( (10 >= counter) ? counter:10) );
                // since counter isn't used in the code after, I changed the value to 10 as the maximum.

                // goes through the whole array looking for the matching values
                for ( piMatches = matches; piMatches < piMatchesEnd; piMatches++)
                {
                    if(*piMatches != -1) {
                        printf(" [%d...%ld]", *piMatches, *piMatches + strlen(wordLookUp)-1);
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
                break;
            
            //----------------------------------------------------------//

            case ('1'):
                
                printf("Enter a line of text:\n"); 
                fgets(userInput, SIZE, stdin);
                if(userInput[0] == '\n')
                    break;

                // cleaning \n character
                if (myStrCh('\n', userInput) == 0) {
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
                break;
                default:
                {
                printf("insert a valid option: ");
                ans = getchar();
                }
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

int wordFound( char pStr[], char word[], int loc[], int mLoc) {
    int * pLoc = loc, counter = 0, matches = 0, objective = strlen(word);

    char * piStr = pStr, * pEnd = piStr + strlen(pStr);
    char * piWord = word, *piWordEnd = piWord + strlen(word);
	for ( ; piStr < pEnd; piStr++, piWord++) {
        if(*piStr == *piWord && piWord < piWordEnd) {
            matches++;
        }
        else {
            piWord = word;
            matches = 0;
        }
        if (matches == objective){
            matches = 0;
            counter++;
            *pLoc = (strlen(word) - (piStr - pStr));
        }
    }

	return counter;
}
