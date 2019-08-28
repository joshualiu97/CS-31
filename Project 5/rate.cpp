#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cassert>
#include <cctype>
#include <cstring>
using namespace std;

const int MAX_WORD_LENGTH = 20;

int makeProper(char word1[][MAX_WORD_LENGTH + 1],
	char word2[][MAX_WORD_LENGTH + 1],
	int separation[],
	int nPatterns);

int rate(const char document[],
	const char word1[][MAX_WORD_LENGTH + 1],
	const char word2[][MAX_WORD_LENGTH + 1],
	const int separation[],
	int nPatterns);

int main()
{
	// Test cases for makeProper
	const int TEST1_NRULES = 8;
	char test1w1[TEST1_NRULES][MAX_WORD_LENGTH + 1] = { "mad", "deranged", "NEFARIOUS", "half-witted", "robot", "plot", "have", "NeFaRiOuS" };
	char test1w2[TEST1_NRULES][MAX_WORD_LENGTH + 1] = { "scientist", "robot", "PLOT", "assistant", "deranged", "Nefarious", "mad", "pLoT" };
	int test1dist[TEST1_NRULES] = { 1, 2, 3, 4, 5, 6, -12, 7 }; 
	assert(makeProper(test1w1, test1w2, test1dist, TEST1_NRULES) == 3); // remove rows with negative separation and nonalphabetical words
		//Words that appear twice intercahgnably in word1 and word2 are listed only once with the greatest separation
		//All upper case letters are changed to lower case letters
	
	const int TEST3_NRULES = 3;
	char test3w1[TEST3_NRULES][MAX_WORD_LENGTH + 1] = { "", "", "" };
	char test3w2[TEST3_NRULES][MAX_WORD_LENGTH + 1] = { "hello", " ", " " };
	int test3dist[TEST3_NRULES] = { 1, 2, 3 };
	assert(makeProper(test3w1, test3w2, test3dist, TEST3_NRULES) == 0); // blank char array and spaces return 0 for nPatterns
	
	const int TEST4_NRULES = 1;
	char test4w1[TEST4_NRULES][MAX_WORD_LENGTH + 1] = { };
	char test4w2[TEST4_NRULES][MAX_WORD_LENGTH + 1] = { };
	int test4dist[TEST4_NRULES] = { };
	assert(makeProper(test4w1, test4w2, test4dist, TEST4_NRULES) == 0); // blank char array and spaces return 0 for nPatterns
	
	const int TEST5_NRULES = 1;
	char test5w1[TEST5_NRULES][MAX_WORD_LENGTH + 1] = { "chicken" };
	char test5w2[TEST5_NRULES][MAX_WORD_LENGTH + 1] = { "turkey" };
	int test5dist[TEST5_NRULES] = { 15 };
	assert(makeProper(test5w1, test5w2, test5dist, TEST5_NRULES) == 1); // one correct row of elements only, return nPatters = 1
	
	const int TEST6_NRULES = 1;
	char test6w1[TEST6_NRULES][MAX_WORD_LENGTH + 1] = { "chicken" };
	char test6w2[TEST6_NRULES][MAX_WORD_LENGTH + 1] = { "turkey" };
	int test6dist[TEST6_NRULES] = { -15 };
	assert(makeProper(test6w1, test6w2, test6dist, TEST6_NRULES) == 0); // separation is negative, return 0
	assert(makeProper(test6w1, test6w2, test6dist, -1) == 0); // negative nPatterns, return 0

	// Test cases for rate
	const int TEST2_NRULES = 4;
	char test2w1[TEST2_NRULES][MAX_WORD_LENGTH + 1] = { "mad", "deranged", "nefarious", "have" };
	char test2w2[TEST2_NRULES][MAX_WORD_LENGTH + 1] = { "scientist", "robot", "plot", "mad" };
	int test2dist[TEST2_NRULES] = { 1, 3, 0, 12 };
	assert(rate("The mad UCLA scientist unleashed a deranged evil giant robot.", test2w1, test2w2, test2dist, TEST2_NRULES) == 2); // count correct number of words, return 2
	assert(rate("The mad UCLA scientist unleashed    a deranged robot.", test2w1, test2w2, test2dist, TEST2_NRULES) == 2); // extra spaces in document string, ignore and return 2
	assert(rate("**** 2018 ****", test2w1, test2w2, test2dist, TEST2_NRULES) == 0); // blank string when nonalphabetical chars are ignored, return 0
	assert(rate("  That plot: NEFARIOUS!", test2w1, test2w2, test2dist, TEST2_NRULES) == 1); // ignore nonalphabetical characters and count matches, return 1
	assert(rate("That scientist said two mad scientists suffer from deranged-robot fever.", test2w1, test2w2, test2dist, TEST2_NRULES) == 0); // no mathces, return 0
	
	const int TEST7_NRULES = 4;
	char test7w1[TEST7_NRULES][MAX_WORD_LENGTH + 1] = { "chicken", "good", "golden", "sauce" };
	char test7w2[TEST7_NRULES][MAX_WORD_LENGTH + 1] = { "nuggets", "taste", "crispy", "hot" };
	int test7dist[TEST7_NRULES] = { 4, 1, 3, 2 };
	assert(rate("   *The9 chi5cken nu*ggets taste so  sooo good# with sauce w%hen   they a#re hot.", test7w1, test7w2, test7dist, TEST7_NRULES) == 1); // ignore nonalphabetical chars, return 1
	assert(rate("   *The9  nu*ggets chi5cken good# so  sooo taste  with sauce w%hen   they a#re hot.", test7w1, test7w2, test7dist, TEST7_NRULES) == 1); // swap words from previous case, return 1
	assert(rate("chicken golden crispy golden green nuggets   ", test7w1, test7w2, test7dist, TEST7_NRULES) == 2); // only count matches once, return 2
	assert(rate("  [purple chicken golde%n c3rispy go&&lden gre*e()n nug!@#$gets   ", test7w1, test7w2, test7dist, TEST7_NRULES) == 2); // only count matches once, random spaces beofre and after, return 2
	assert(rate("  [purple chicken golde%n c3rispy go&&lden  nug!@#$gets   ", test7w1, test7w2, test7dist, TEST7_NRULES) == 2); // make sure program does not check out of bounds, return 2
	assert(rate("  [purple nug!@#$gets golde%n c3rispy go&&lden gre*e()n chicken    ", test7w1, test7w2, test7dist, TEST7_NRULES) == 2); // same as previous test but swapped, ensure it works as well, return 2
	assert(rate("  ***7&&&883285%$^#74567%*%$&%", test7w1, test7w2, test7dist, TEST7_NRULES) == 0); // empty string after nonalphabetical characters and spaces are considered, return 0
	assert(rate(" good  ", test7w1, test7w2, test7dist, TEST7_NRULES) == 0); // one word that has is a word in word1 but not word2, return 0
	assert(rate("chicken golden blue crispy golden green nuggets   ", test7w1, test7w2, test7dist, TEST7_NRULES) == 1); // ensure separation works at beginning of string wihtout accessing invalid spots, return 1
	assert(rate("nuggets golden blue crispy golden green    chicken", test7w1, test7w2, test7dist, TEST7_NRULES) == 1); // ensure separation works at end of string without accessing invalid sports, return 1
	
	cout << "All tests succeeded" << endl;
}

int makeProper(char word1[][MAX_WORD_LENGTH + 1],
	char word2[][MAX_WORD_LENGTH + 1],
	int separation[],
	int nPatterns)
{
	if (nPatterns <= 0)
	{
		return 0;
	}
	int numOfWords = nPatterns;

	// Remove all strings with non-alphabetical characters
	for (int i = 0; i < numOfWords; i++) // Check word1
	{
		for (int j = 0; word1[i][j] != '\0'; j++)
		{
			if (!isalpha(word1[i][j])) // If has nonalphabetical, remove whole row
			{
				for (int k = i; k < numOfWords - 1; k++)
				{
					//word1[k][MAX_WORD_LENGTH + 1] = word1[k + 1][MAX_WORD_LENGTH + 1]; // Works as well
					strcpy(word1[k], word1[k + 1]);
				}
				for (int l = i; l < numOfWords - 1; l++)
				{
					//word2[l][MAX_WORD_LENGTH + 1] = word2[l + 1][MAX_WORD_LENGTH + 1]; // Works as well
					strcpy(word2[l], word2[l + 1]);
				}
				for (int m = i; m < numOfWords - 1; m++)
				{
					separation[m] = separation[m + 1];
				}

				numOfWords -= 1;
				break;
			}
		}
		if (numOfWords != nPatterns) // Decrease nPatterns to match number of elements
		{
			nPatterns -= 1;
			i -= 1; // Need to recheck current spot since nonalphabetical element was removed from the same spot
		}
	}

	for (int i = 0; i < numOfWords; i++) // Check word2
	{
		for (int j = 0; word2[i][j] != '\0'; j++)
		{
			if (!isalpha(word2[i][j])) // If has nonalphabetical, remove whole row
			{
				for (int k = i; k < numOfWords - 1; k++)
				{
					strcpy(word2[k], word2[k + 1]);
				}
				for (int l = i; l < numOfWords - 1; l++)
				{
					strcpy(word1[l], word1[l + 1]);
				}
				for (int m = i; m < numOfWords - 1; m++)
				{
					separation[m] = separation[m + 1];
				}

				numOfWords -= 1;
				break;
			}
		}
		if (numOfWords != nPatterns) // Decrease nPatterns to match number of elements
		{
			nPatterns -= 1;
			i -= 1; // Need to recheck current spot since nonalphabetical element was removed from the same spot
		}
	}

	// Convert strings to lower case
	for (int i = 0; i < nPatterns; i++)
	{
		for (int j = 0; word1[i][j] != '\0'; j++)
		{
			if (!islower(word1[i][j]))
			{
				word1[i][j] = tolower(word1[i][j]);
			}
		}
	}
	for (int i = 0; i < nPatterns; i++)
	{
		for (int j = 0; word2[i][j] != '\0'; j++)
		{
			if (!islower(word2[i][j]))
			{
				word2[i][j] = tolower(word2[i][j]);
			}
		}
	}
	
	// Look for empty or blank string
	for (int i = 0; i < nPatterns; i++)
	{
		if (word1[i][0] == '\0') // If empty/blank string in word1, remove that row of patterns
		{
			for (int k = i; k < nPatterns - 1; k++)
			{
				strcpy(word2[k], word2[k + 1]);
			}
			for (int l = i; l < nPatterns - 1; l++)
			{
				strcpy(word1[l], word1[l + 1]);
			}
			for (int m = i; m < nPatterns - 1; m++)
			{
				separation[m] = separation[m + 1];
			}
			nPatterns--;
			i--;
		}
	}
	for (int i = 0; i < nPatterns; i++)
	{
		if (word2[i][0] == '\0') // If empty/blank string in word2, remove that row of patterns
		{
			for (int k = i; k < nPatterns - 1; k++)
			{
				strcpy(word2[k], word2[k + 1]);
			}
			for (int l = i; l < nPatterns - 1; l++)
			{
				strcpy(word1[l], word1[l + 1]);
			}
			for (int m = i; m < nPatterns - 1; m++)
			{
				separation[m] = separation[m + 1];
			}
			nPatterns--;
			i--;
		}
	}

	// Look for negative separation value and remove
	for (int i = 0; i < nPatterns; i++)
	{
		if (separation[i] < 0)
		{
			for (int k = i; k < nPatterns - 1; k++)
			{
				strcpy(word2[k], word2[k + 1]);
			}
			for (int l = i; l < nPatterns - 1; l++)
			{
				strcpy(word1[l], word1[l + 1]);
			}
			for (int m = i; m < nPatterns - 1; m++)
			{
				separation[m] = separation[m + 1];
			}
			nPatterns--;
			i--;
		}
	}

	// Check word1 word with other word1 words
	int cycleThroughArray = 0;
	
	while (cycleThroughArray != nPatterns)
	{
		int i = cycleThroughArray;
		while (i != nPatterns - 1)
		{
			int j = i + 1;
			while (j < nPatterns) // If there is a word in word1 that matches a word int word1 after the current word, check word2 for a match
			{
				if (strcmp(word1[i], word1[j]) == 0)
				{
					if (strcmp(word2[i], word2[j]) == 0)
					{
						if (separation[i] < separation[j]) // If they match, remove the element with the smaller separation value
						{
							for (int k = i; k < numOfWords - 1; k++)
							{
								//word1[k][MAX_WORD_LENGTH + 1] = word1[k + 1][MAX_WORD_LENGTH + 1];
								strcpy(word1[k], word1[k + 1]);
							}
							for (int l = i; l < numOfWords - 1; l++)
							{
								//word2[l][MAX_WORD_LENGTH + 1] = word2[l + 1][MAX_WORD_LENGTH + 1];
								strcpy(word2[l], word2[l + 1]);
							}
							for (int m = i; m < numOfWords - 1; m++)
							{
								separation[m] = separation[m + 1];
							}
							nPatterns -= 1;
						}
						else
						{
							for (int k = j; k < numOfWords - 1; k++)
							{
								//word1[k][MAX_WORD_LENGTH + 1] = word1[k + 1][MAX_WORD_LENGTH + 1];
								strcpy(word1[k], word1[k + 1]);
							}
							for (int l = j; l < numOfWords - 1; l++)
							{
								//word2[l][MAX_WORD_LENGTH + 1] = word2[l + 1][MAX_WORD_LENGTH + 1];
								strcpy(word2[l], word2[l + 1]);
							}
							for (int m = j; m < numOfWords - 1; m++)
							{
								separation[m] = separation[m + 1];
							}
							nPatterns -= 1;
						}
						i--; // Need to recheck at previous location after removing an element
					}
					break;
				}
				j++;
			}
			i++;
		}
		cycleThroughArray++;
	}

	// Check word2 word and word1 word
	int cycleThroughArray2 = 0;
	
	while (cycleThroughArray2 != nPatterns)
	{
		int i = cycleThroughArray2;
		while (i != nPatterns - 1)
		{
			int j = i + 1;
			while (j < nPatterns) // If there is a word in word1 that matches a word in word2 after the current word, check for a match in word1 and word2
			{
				if (strcmp(word1[i], word2[j]) == 0)
				{
					if (strcmp(word2[i], word1[j]) == 0)
					{
						if (separation[i] < separation[j]) // If they match, remove the element with the smaller separation value
						{
							for (int k = i; k < numOfWords - 1; k++)
							{
								//word1[k][MAX_WORD_LENGTH + 1] = word1[k + 1][MAX_WORD_LENGTH + 1];
								strcpy(word1[k], word1[k + 1]);
							}
							for (int l = i; l < numOfWords - 1; l++)
							{
								//word2[l][MAX_WORD_LENGTH + 1] = word2[l + 1][MAX_WORD_LENGTH + 1];
								strcpy(word2[l], word2[l + 1]);
							}
							for (int m = i; m < numOfWords - 1; m++)
							{
								separation[m] = separation[m + 1];
							}
							nPatterns -= 1;
						}
						else
						{
							for (int k = j; k < numOfWords - 1; k++)
							{
								//word1[k][MAX_WORD_LENGTH + 1] = word1[k + 1][MAX_WORD_LENGTH + 1];
								strcpy(word1[k], word1[k + 1]);
							}
							for (int l = j; l < numOfWords - 1; l++)
							{
								//word2[l][MAX_WORD_LENGTH + 1] = word2[l + 1][MAX_WORD_LENGTH + 1];
								strcpy(word2[l], word2[l + 1]);
							}
							for (int m = j; m < numOfWords - 1; m++)
							{
								separation[m] = separation[m + 1];
							}
							nPatterns -= 1;
						}
						i--; // Need to recheck at previous location after removing an element
					}
					break; 
				}
				j++;
			}
			i++;
		}
		cycleThroughArray2++;
	}

	// Check word2 word with other word2 words
	int cycleThroughArray3 = 0;

	while (cycleThroughArray3 != nPatterns)
	{
		int i = cycleThroughArray3;
		while (i != nPatterns - 1)
		{
			int j = i + 1;
			while (j < nPatterns) // If there is a word in word2 that matches a word in word2 after the current word, check word1 for a match
			{
				if (strcmp(word2[i], word2[j]) == 0)
				{
					if (strcmp(word1[i], word1[j]) == 0)
					{
						if (separation[i] < separation[j]) // If they match, remove the element with the smaller separation value
						{
							for (int k = i; k < numOfWords - 1; k++)
							{
								//word1[k][MAX_WORD_LENGTH + 1] = word1[k + 1][MAX_WORD_LENGTH + 1];
								strcpy(word1[k], word1[k + 1]);
							}
							for (int l = i; l < numOfWords - 1; l++)
							{
								//word2[l][MAX_WORD_LENGTH + 1] = word2[l + 1][MAX_WORD_LENGTH + 1];
								strcpy(word2[l], word2[l + 1]);
							}
							for (int m = i; m < numOfWords - 1; m++)
							{
								separation[m] = separation[m + 1];
							}
							nPatterns -= 1;
						}
						else
						{
							for (int k = j; k < numOfWords - 1; k++)
							{
								//word1[k][MAX_WORD_LENGTH + 1] = word1[k + 1][MAX_WORD_LENGTH + 1];
								strcpy(word1[k], word1[k + 1]);
							}
							for (int l = j; l < numOfWords - 1; l++)
							{
								//word2[l][MAX_WORD_LENGTH + 1] = word2[l + 1][MAX_WORD_LENGTH + 1];
								strcpy(word2[l], word2[l + 1]);
							}
							for (int m = j; m < numOfWords - 1; m++)
							{
								separation[m] = separation[m + 1];
							}
							nPatterns -= 1;
						}
						i--; // Need to recheck at previous location after removing an element
					}
					break;
				}
				j++;
			}
			i++;
		}
		cycleThroughArray3++;
	}

	// Check word1 word with word2 word

	int cycleThroughArray4 = 0;

	while (cycleThroughArray4 != nPatterns)
	{
		int i = cycleThroughArray4;
		while (i != nPatterns - 1)
		{
			int j = i + 1;
			while (j < nPatterns) // If there is a word in word2 that matches a word in word1 after the current word, check for a match in word1 and word2
			{
				if (strcmp(word2[i], word1[j]) == 0)
				{
					if (strcmp(word1[i], word2[j]) == 0)
					{
						if (separation[i] < separation[j]) // If they match, remove the element with the smaller separation value
						{
							for (int k = i; k < numOfWords - 1; k++)
							{
								//word1[k][MAX_WORD_LENGTH + 1] = word1[k + 1][MAX_WORD_LENGTH + 1];
								strcpy(word1[k], word1[k + 1]);
							}
							for (int l = i; l < numOfWords - 1; l++)
							{
								//word2[l][MAX_WORD_LENGTH + 1] = word2[l + 1][MAX_WORD_LENGTH + 1];
								strcpy(word2[l], word2[l + 1]);
							}
							for (int m = i; m < numOfWords - 1; m++)
							{
								separation[m] = separation[m + 1];
							}
							nPatterns -= 1;
						}
						else
						{
							for (int k = j; k < numOfWords - 1; k++)
							{
								//word1[k][MAX_WORD_LENGTH + 1] = word1[k + 1][MAX_WORD_LENGTH + 1];
								strcpy(word1[k], word1[k + 1]);
							}
							for (int l = j; l < numOfWords - 1; l++)
							{
								//word2[l][MAX_WORD_LENGTH + 1] = word2[l + 1][MAX_WORD_LENGTH + 1];
								strcpy(word2[l], word2[l + 1]);
							}
							for (int m = j; m < numOfWords - 1; m++)
							{
								separation[m] = separation[m + 1];
							}
							nPatterns -= 1;
						}
						i--; // Need to recheck at previous location after removing an element
					}
					break;
				}
				j++;
			}
			i++;
		}
		cycleThroughArray4++;
	}

	return nPatterns;
}

int rate(const char document[],
	const char word1[][MAX_WORD_LENGTH + 1],
	const char word2[][MAX_WORD_LENGTH + 1],
	const int separation[],
	int nPatterns)
{
	const int STORE_CHARS = 300; // Array size, ensure it takes more than 250 characters
	int matches = 0; // Counts how many matches there are within the document
	
	if (nPatterns <= 0) // Case where nPatterns is 0 or negative
	{
		return 0;
	}

	// Convert document into correct syntax
	char correctSyntaxDoc[STORE_CHARS]; // Create array of correct syntax, takes in the info from document
	int lookInDocument = 0;
	for (int i = 0; document[i] != '\0'; i++)
	{
		if (isalpha(document[i]) || isblank(document[i]))
		{
			correctSyntaxDoc[lookInDocument] = document[i];
			lookInDocument++;
		}
	}
	correctSyntaxDoc[lookInDocument] = '\0';
	
	for (int i = 0; correctSyntaxDoc[i] != '\0'; i++) // Convert all uppercase letters to lowercase letters
	{
		if (isupper(correctSyntaxDoc[i]))
		{
			correctSyntaxDoc[i] = tolower(correctSyntaxDoc[i]);
		}
	}

	// Add space to beginning and end of string for the program to process string
	char manipulateDoc[STORE_CHARS]; // Create another array to manipulate and check
	manipulateDoc[0] = ' ';
	int pos;
	for (pos = 0; correctSyntaxDoc[pos] != '\0'; pos++)
	{
		manipulateDoc[pos + 1] = correctSyntaxDoc[pos];
	}
	manipulateDoc[pos + 1] = ' ';
	manipulateDoc[pos + 2] = '\0';
	
	char documentArray[STORE_CHARS][STORE_CHARS]; // Create a 2D character array to store the words from the document
	
	int documentArrayElements = 0;

	while (manipulateDoc[0] != '\0') // Put all the words in a char array for easier comparison
	{
		while (isspace(manipulateDoc[0])) // Remove spaces to see the next word
		{
			int c = 0;
			for (c = 0; manipulateDoc[c] != '\0'; c++)
			{
				manipulateDoc[c] = manipulateDoc[c + 1];
			}
			manipulateDoc[c] = '\0';
		}
		int wordLength = 0;

		while (manipulateDoc[wordLength] != ' ') // Find word length to store the word in the character array
		{
			wordLength++;
			if (wordLength > 255) // Ensure there are no out of bounds errors
			{
				break;
			}
		}
		
		if (manipulateDoc[0] == '\0') // break out of this loop after reaching the end of the string
		{
			break;
		}
		else // Store the characters in the character array based on the word length
		{
			int a = 0;
			for (a = 0; a < wordLength; a++)
			{
				documentArray[documentArrayElements][a] = manipulateDoc[a];
			}
			documentArray[documentArrayElements][a] = '\0';

			int b = 0;
			for (b = 0; manipulateDoc[b] != '\0'; b++)
			{
				manipulateDoc[b] = manipulateDoc[b + wordLength];
			}
			manipulateDoc[b] = '\0';

			documentArrayElements++;
		}
	}
	
	// DocumentArrayElements is the number of elements in the document string
	int cycleThroughDoc = 0;
	for (int i = 0; i < nPatterns; i++)
	{
		cycleThroughDoc = 0;
		while (cycleThroughDoc != documentArrayElements)
		{
			if (strcmp(word1[i], documentArray[cycleThroughDoc]) == 0) // If a word in word1 matches a word in the document, check if word2 matches another word based on the separation
			{
				int lowerBound = cycleThroughDoc - (separation[i] + 1); // Create lower bound to check
				int upperBound = cycleThroughDoc + (separation[i] + 1); // Create upper bound to check
				if (lowerBound < 0) // Make sure the bounds do not go out of the array range
				{
					lowerBound = 0;
				}
				if (upperBound > documentArrayElements - 1)
				{
					upperBound = documentArrayElements - 1;
				}
				int holdCount = matches; // Keeps track of matches
				for (int j = lowerBound; j < upperBound + 1; j++)
				{
					if (j == cycleThroughDoc) // Do not consider word2 in the case where word1 is equal to word2
					{
						continue;
					}
						if (strcmp(word2[i], documentArray[j]) == 0)
					{
						matches++;
						break;
					}
				}
				if (matches != holdCount) // Break if a match is found so we can investigate the next pattern
				{
					break;
				}
			}
			cycleThroughDoc++;
		}
	}

	return matches;
}