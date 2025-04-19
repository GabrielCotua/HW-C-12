// HW 12 Gabriel Cotua
#include <stdio.h>
#include <string.h>

#define SIZE 41		  // size of the input character array
#define MAXMATCHES 10 // max matches
#define FLUSH while (getchar() != '\n');

int stringIsAt(char pStr[], char lookup[], int loc[], int mLoc);
void resetMatches(int matches[], int *piMatches, int *piMatchesEnd);
int myStrCh(const char goal, char pStr[]);

int main(void)
{
	printf("\n\n|#####################|\n|HW #12, Gabriel Cotua|\n|#####################|\n\n");

	char userInput[SIZE], lookUp[SIZE];
	// [userInput] is where the string to look for will be,
	// [lookUp will] be the string that we are going to look for in userInput

	char *piUserInput = userInput, *piUserInputEnd = userInput + SIZE; // char pointers
	// [piUserInput] used as the pointer that will go through userInput array
	// [piUserInputEnd] is the endpoint reference

	int matches[MAXMATCHES], counter = 0;
	// [matches] saves the index of the first character where [lookUp] and [userInput] are equal
	// [counter] keeps the count of occurrences found

	int *piMatches = matches, *piMatchesEnd = matches + MAXMATCHES; // int pointers
	// [piMatches] used as the pointer that will go through matches array
	// [piMatchesEnd] is the endpoint reference

	while (printf("Enter a line of text to search in (ctr+c or ENTER to exit): \n"), fgets(userInput, SIZE, stdin) && userInput[0] != '\n')
	{

		// cleaning \n character
		if (myStrCh('\n', userInput) == 0)
		{ // checks for '\n' character in the string, otherwise means that is in the buffer, so we clear it
			FLUSH;
		}
		else
		{
			userInput[strlen(userInput) - 1] = '\0'; // turn '\n' into '\0' character, to avoid template errors
		}

		resetMatches(matches, piMatches, piMatchesEnd); // reseting the array of matches
		// userInput[strlen(userInput)-1] = '\0'; // setting an ending point
		printf("Your Input: %s\n", userInput);
		printf("Input a string to look for: ");
		fgets(lookUp, SIZE, stdin); // getting user string to lookup for

		// make sure user doesn't look for a '\n'
		while (lookUp[0] == '\n')
		{
			printf("Input a string to look for: ");
			fgets(lookUp, SIZE, stdin); // getting user string to lookup for
		}

		if (myStrCh('\n', lookUp) == 0) // if it doesn't have a '\n' character, it will clear the buffer
		{
			FLUSH;
		}
		else
		{
			lookUp[strlen(lookUp) - 1] = '\0'; // turn '\n' into an '\0' character to acoid template errors
		}

		counter = stringIsAt(userInput, lookUp, matches, MAXMATCHES);

		printf("The string '%s' was found %d time(s).\n", lookUp, counter);

		if (counter > 0)
		{

			printf("The first %d matches is/are at:", counter = ((10 >= counter) ? counter : 10));

			// since counter isn't used in the code after, I changed the value to 10 as the maximum.

			// goes through the whole array looking for the matching values
			for (piMatches = matches; piMatches < piMatchesEnd; piMatches++)
			{
				if (*piMatches != -1)
				{
					printf(" [%d]", *piMatches);
				}
			}
			printf(" in the string\n");
			printf("\"%s\"\n ", userInput);
		}
		else
		{
			printf("No matches.\n");
		}

		// using user input length, we are going to get all the locations of occurrences
		for (piUserInput = userInput, piMatches = matches; piUserInput < piUserInputEnd; piUserInput++)
		{
			if (*piMatches != -1 && *piMatches == piUserInput - userInput)
			{
				putchar('^');
				piMatches++;
			}
			else
			{
				putchar(' ');
			}
		}
		putchar('\n');
	}
	printf("Bye byee.\n");

	return 0;
}

/*
	@param pStr[] userInput String
	@param ch character to look for
	@param loc[] array where the index of the first matches will be save
	@param mLoc size of loc[]
*/
int stringIsAt(char *pStr, char *lookup, int *loc, int mLoc)
{

	int *pLoc = loc, counter = 0, chain = 0, possibleLocation = 0;
	char *piStr = pStr, *piStrEnd = piStr + strlen(pStr);
	char *piLookup = lookup, *piLookupEnd = piLookup + strlen(lookup);
	int lenLookup = strlen(lookup);

	for (; piStr < piStrEnd; piStr++)
	{

		if (*piStr == *piLookup && piLookup <= piLookupEnd)
		{

			if (chain == 0) // take the location of the first occurance of the string
				possibleLocation = piStr - pStr;
	
			chain++;
			piLookup++;
			
			if (chain == lenLookup)
			{
				if (pLoc - loc < mLoc)
				{
					*pLoc = possibleLocation;
					pLoc++;
				}
				counter++;

				// reset for next potential match
				piLookup = lookup;
				chain = 0;

			}
		}
		else
		{
			// reset search
			chain = 0;
			piLookup = lookup;
		}
	}
	return counter;
}
/*
	@param matches[] array where
*/
void resetMatches(int matches[], int *piMatches, int *piMatchesEnd)
{
	// starting array
	for (piMatches = matches; piMatches < piMatchesEnd; piMatches++)
		*piMatches = -1;
}

/*
	@param goal is the char you want to find
	@param pStr[] array of character that you want to check
	return 1 once the first match was found, return 0 otherwise
 */
int myStrCh(const char goal, char pStr[])
{

	for (char *piStr = pStr, *piStrEnd = pStr + strlen(pStr); piStr < piStrEnd; piStr++)
	{
		if (*piStr == goal)
		{
			return 1;
		}
	}

	return 0;
}
/*


|#####################|
|HW #12, Gabriel Cotua|
|#####################|

Enter a line of text to search in (ctr+c or ENTER to exit):
alskdjfasdfasfasasafsdfjajsfajsdfjasasasfjasdjfajsasaas
Your Input: alskdjfasdfasfasasafsdfjajsfajsdfjasasas
Input a string to look for: as
The string 'as' was found 7 time(s).
The first 7 matches is/are at: [7] [11] [14] [16] [34] [36] [38] in the string
"alskdjfasdfasfasasafsdfjajsfajsdfjasasas"
        ^   ^  ^ ^                 ^ ^ ^
Enter a line of text to search in (ctr+c or ENTER to exit):
alksdjflkasjdfkljjhohohohoasjldfkjaslkdfjhojalsdkfjaho
Your Input: alksdjflkasjdfkljjhohohohoasjldfkjaslkdf
Input a string to look for: ho
The string 'ho' was found 4 time(s).
The first 4 matches is/are at: [18] [20] [22] [24] in the string
"alksdjflkasjdfkljjhohohohoasjldfkjaslkdf"
                   ^ ^ ^ ^
Enter a line of text to search in (ctr+c or ENTER to exit):
asdfhasd jalskd laksjdk jaslkdfj laksgasj dkfjasldkfj
Your Input: asdfhasd jalskd laksjdk jaslkdfj laksgas
Input a string to look for:  
The string ' ' was found 4 time(s).
The first 4 matches is/are at: [8] [15] [23] [32] in the string
"asdfhasd jalskd laksjdk jaslkdfj laksgas"
         ^      ^       ^        ^
Enter a line of text to search in (ctr+c or ENTER to exit):

Bye byee.
*/