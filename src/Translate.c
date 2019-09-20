#include "Translate.h"
#include <ctype.h>

char* translateIfAndLoops(char* fileContents)
{
	char* translatedFileContents = malloc(strlen(fileContents) + 256);
	int pointer = 0;
	if(translatedFileContents == NULL)
	{
		fprintf(stderr, "ERROR: Not enough memory!");
		exit(1);
	}
	char* tokens = strtok(fileContents,"\n");
	char ifState = 0;
	char endIfState = 0;
	char lookForSemiColon = 0;
	char elseState = 0;
	while(tokens != NULL)
	{
		for(int i = 0; i < strlen(tokens); i++)
		{
			if(tokens[i] == 'i' && ifState == 0 && endIfState == 0 && elseState == 0)
			{
				ifState = 1;
			}
			else if(tokens[i] == 'f' && ifState == 1)
			{
				ifState = 2;
			}
			else if(tokens[i] == '(' && ifState == 2)
			{
				lookForSemiColon = 1;
				ifState = 0;
			}
			else if(tokens[i] == ' ' && ifState == 2)
			{
				continue;
			}
			else if(lookForSemiColon)
			{
				if(tokens[i] == ';')
				{	
					translatedFileContents[pointer++] = '{';
					lookForSemiColon = 0;
					continue;
				}
			}
			else if(tokens[i] == 'e' && endIfState == 0 && ifState == 0 && elseState == 0)
			{
				endIfState = 1;
				elseState = 1;
				continue;
			}
			else if(tokens[i] == 'n' && endIfState == 1)
			{
				endIfState = 2;
				elseState = 0;
				continue;
			}
			else if(tokens[i] == 'd' && endIfState == 2)
			{
				endIfState = 3;
				continue;
			}
			else if(tokens[i] == 'i' && endIfState == 3)
			{
				endIfState = 4;
				continue;
			}
			else if(tokens[i] == 'f' && endIfState == 4)
			{
				endIfState = 5;
				continue;
			}
			else if(tokens[i] == ';' && endIfState == 5)
			{
				endIfState = 0;
				translatedFileContents[pointer++] = '}';
				continue;
			}
			else if(tokens[i] == 'l' && elseState == 1)
			{
				elseState = 2;
				endIfState = 0;
				translatedFileContents[pointer++] = 'e';
			}
			else if(tokens[i] == 's' && elseState == 2)
			{
				elseState = 3;
				continue;
			}
			else if(tokens[i] == 'e' && elseState == 3)
			{
				elseState = 4;
				continue;
			}
			else if(tokens[i] == ';' && elseState == 4)
			{
				pointer -= 2;
				translatedFileContents[pointer++] = '}';
				translatedFileContents[pointer++] = 'e';
				translatedFileContents[pointer++] = 'l';
				translatedFileContents[pointer++] = 's';
				translatedFileContents[pointer++] = 'e';
				translatedFileContents[pointer++] = '{';
				elseState = 0;
				continue;
			}
			else if(tokens[i] == ' ' && elseState == 4)
			{
				pointer -= 2;
				translatedFileContents[pointer++] = '}';
				translatedFileContents[pointer++] = 'e';
				translatedFileContents[pointer++] = 'l';
				translatedFileContents[pointer++] = 's';
				translatedFileContents[pointer++] = 'e';
				translatedFileContents[pointer++] = ' ';
				elseState = 5;
				continue;
			}
			else if(tokens[i] == 'i' && elseState == 5)
			{
				elseState = 6;
			}
			else if(tokens[i] == 'f' && elseState == 6)
			{
				elseState = 7;
				lookForSemiColon = 1;
			}
			else if(tokens[i] == ';' && elseState == 7)
			{
				translatedFileContents[pointer++] = '{';
				elseState = 0;
				continue;
			}
			else
			{
				if(endIfState == 1 || elseState == 1)
				{
					translatedFileContents[pointer++] = 'e';
				}
				ifState = 0;
				endIfState = 0;
				elseState = 0;
			}
			translatedFileContents[pointer++] = tokens[i];
		}
		tokens = strtok(NULL,"\n");
	}
	translatedFileContents[pointer++] = '\0';
	return translatedFileContents;
}

char* translateVariables(char* fileContents)
{
	char* translatedFileContents = malloc(strlen(fileContents) + 256);
	int pointer = 0;
	if(translatedFileContents == NULL)
	{
		fprintf(stderr, "ERROR: Not enough memory!");
		exit(1);
	}
	char* tokens = strtok(fileContents,"\n");
	char lookForVariableDeclaration = 0;
	char foundStartOfNumber = 0;
	while(tokens != NULL)
	{
		for(int i = 0; i < strlen(tokens);i++)
		{
			if(tokens[i] == 'v' && lookForVariableDeclaration == 0)
			{
				lookForVariableDeclaration = 1;
			}
			else if(tokens[i] == 'a' && lookForVariableDeclaration == 1)
			{
				lookForVariableDeclaration = 2;
			}
			else if(tokens[i] == 'r' && lookForVariableDeclaration == 2)
			{
				lookForVariableDeclaration = 3;
			}
			else if(tokens[i] == ' ' && lookForVariableDeclaration == 3)
			{
				//Appened String
				translatedFileContents[pointer++] = 'c';
				translatedFileContents[pointer++] = 'h';
				translatedFileContents[pointer++] = 'a';
				translatedFileContents[pointer++] = 'r';
				translatedFileContents[pointer++] = '*';
				translatedFileContents[pointer++] = ' ';
				lookForVariableDeclaration = 4;
			}
			else if(tokens[i] == ' ' && lookForVariableDeclaration == 4)
			{
				continue;
			}
			else if(lookForVariableDeclaration == 4)
			{
				if(isdigit(tokens[i]))
				{
					translatedFileContents[pointer++] = '"';
					translatedFileContents[pointer++] = tokens[i];
					foundStartOfNumber = 1;
					lookForVariableDeclaration = 5;
				}
				else
				{
					translatedFileContents[pointer++] = tokens[i];
				}
			}
			else if(tokens[i] == ';' && lookForVariableDeclaration == 5)
			{
				if(foundStartOfNumber)
				{
					translatedFileContents[pointer++] = '"';
					translatedFileContents[pointer++] = tokens[i];
					foundStartOfNumber = 0;
				}
				else
				{
					translatedFileContents[pointer++] = tokens[i];
				}
				lookForVariableDeclaration = 0;
			}
			else
			{
				translatedFileContents[pointer++] = tokens[i];
				lookForVariableDeclaration = 0;
			}
		}
		tokens = strtok(NULL,"\n");
	}
	translatedFileContents[pointer++] = '\0';
	return translatedFileContents;
}

char* translateFunctions(char* fileContents)
{
	char* translatedFileContents = malloc(strlen(fileContents) + 256);
	int pointer = 0;
	if(translatedFileContents == NULL)
	{
		fprintf(stderr, "ERROR: Not enough memory!");
		exit(1);
	}
	char* tokens = strtok(fileContents,"\n");
	char functionState = 0;
	char endFunctionState = 0;
	char foundFunction = 0;

	char printState = 0;
	while(tokens != NULL)
	{
		for(int i = 0; i < strlen(tokens); i++)
		{
			if(tokens[i] == 'f' && functionState == 0 && endFunctionState == 0)
			{
				functionState = 1;
			}
			else if(tokens[i] == 'u' && functionState == 1)
			{
				functionState = 2;
			}
			else if(tokens[i] == 'n' && functionState == 2)
			{
				functionState = 3;
			}
			else if(tokens[i] == 'c' && functionState == 3)
			{
				functionState = 4;
			}
			else if(tokens[i] == 't' && functionState == 4)
			{
				functionState = 5;
			}
			else if(tokens[i] == 'i' && functionState == 5)
			{
				functionState = 6;
			}
			else if(tokens[i] == 'o' && functionState == 6)
			{
				functionState = 7;
			}
			else if(tokens[i] == 'n' && functionState == 7)
			{
				functionState = 8;
			}
			else if(tokens[i] == ' ' && functionState == 8)
			{
				functionState = 0;
				translatedFileContents[pointer++] = 'v';
				translatedFileContents[pointer++] = 'o';
				translatedFileContents[pointer++] = 'i';
				translatedFileContents[pointer++] = 'd';
				translatedFileContents[pointer++] = ' ';
				foundFunction = 1;
			}
			else if(foundFunction)
			{
				if(tokens[i] == ';')
				{
					translatedFileContents[pointer++] = ';';
					foundFunction = 0;
				}
			}
			else if(tokens[i] == 'e' && endFunctionState == 0 && functionState == 0)
			{
				endFunctionState = 1;
			}
			else if(tokens[i] == 'n' && endFunctionState == 1)
			{
				endFunctionState = 2;
			}
			else if(tokens[i] == 'd' && endFunctionState == 2)
			{
				endFunctionState = 3;
			}
			else if(tokens[i] == 'f' && endFunctionState == 3)
			{
				endFunctionState = 4;
			}
			else if(tokens[i] == 'u' && endFunctionState == 4)
			{
				endFunctionState = 5;
			}
			else if(tokens[i] == 'n' && endFunctionState == 5)
			{
				endFunctionState = 6;
			}
			else if(tokens[i] == 'c' && endFunctionState == 6)
			{
				endFunctionState = 7;
			}
			else if(tokens[i] == ';' && endFunctionState == 7)
			{
				endFunctionState = 0;
				translatedFileContents[pointer++] = '}';
			}
			//Translate Print function
			else if(tokens[i] == 'P' && printState == 0 && functionState == 0 && endFunctionState == 0)
			{
				printState = 1;
			}
			else if(tokens[i] == 'r' && printState == 1)
			{
				printState = 2;
			}
			else if(tokens[i] == 'i' && printState == 2)
			{
				printState = 3;
			}
			else if(tokens[i] == 'n' && printState == 3)
			{
				printState = 4;
			}
			else if(tokens[i] == 't' && printState == 4)
			{
				printState = 5;
			}
			else if(tokens[i] == ' ' && printState == 5)
			{
				continue;
			}
			else if(tokens[i] == '(' && printState == 5)
			{
				printState = 0;
				translatedFileContents[pointer++] = 'p';
				translatedFileContents[pointer++] = 'r';
				translatedFileContents[pointer++] = 'i';
				translatedFileContents[pointer++] = 'n';
				translatedFileContents[pointer++] = 't';
				translatedFileContents[pointer++] = 'f';
				translatedFileContents[pointer++] = '(';
			}
			else
			{	
				if(endFunctionState == 1)
				{
					translatedFileContents[pointer++] = 'e';
				}
				if(functionState == 1)
				{
					translatedFileContents[pointer++] = 'f';
				}
				translatedFileContents[pointer++] = tokens[i];
				functionState = 0;
				endFunctionState = 0;
			}
		}
		tokens = strtok(NULL,"\n");
	}
	translatedFileContents[pointer++] = '\0';
	return translatedFileContents;
}

char* translatePointersAndOperators(char* fileContents)
{
	printf("TMP - Begin Translating Pointers and Operators...\n");
	char* translatedFileContents = malloc(strlen(fileContents) + 256);
	int pointer = 0;
	if(translatedFileContents == NULL)
	{
		fprintf(stderr, "ERROR: Not enough memory!");
		exit(1);
	}
	printf("TMP - Created Destination String...\n");
	char* tokenPointer = NULL;
	char* tokens = strtok_r(fileContents,"\n",&tokenPointer);
	printf("TMP - Tokenized fileContents...\n");
	while(tokens != NULL)
	{
		char* statementPointer = NULL;
		char* statement = strtok_r(tokens,";",&statementPointer);
		printf("TMP - Tokenized statement...\n");
		char previousCharacter = ' ';
		while(statement != NULL)
		{
			char numberState = 0;
			for(int i = 0; i < strlen(statement); i++)
			{
				if(statement[i] == '@')
				{
					translatedFileContents[pointer++] = '&';
				}
				else if(statement[i] == '~')
				{
					translatedFileContents[pointer++] = '*';
				}
				else
				{
					if(isdigit(statement[i]) && numberState == 0 && previousCharacter != '"')
					{
						numberState = 1;
						translatedFileContents[pointer++] = '"';
					}
					else if(!isdigit(statement[i]) && numberState == 1)
					{
						numberState = 0;
						translatedFileContents[pointer++] = '"';
					}
					translatedFileContents[pointer++] = statement[i];
				}
				previousCharacter = statement[i];
			}
			statement = strtok_r(NULL,";",&statementPointer);
			translatedFileContents[pointer++] = ';';
		}
		tokens = strtok_r(NULL,"\n",&tokenPointer);
	}
	translatedFileContents[--pointer] = '\0';
	return translatedFileContents;
}
