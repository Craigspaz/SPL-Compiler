#include "SyntaxCheck.h"
#include <string.h>

int verifySyntax(char* fileContents)
{
	if(!verifyAllLinesEndWithSemiColons(fileContents) || !verifyAllLoopsEnd(fileContents) || !verifyAllIfStructuresEnd(fileContents) || !verifyAllFunctionDefinitionsEnd(fileContents) || !verifyAllParenthesesEnd(fileContents))
	{
		return 0;
	}
	return 1;
}


int verifyAllParenthesesEnd(char* fileContents)
{
	int counter = 0;
	char* tokens = strtok(fileContents,"\n");
	while(tokens != NULL)
	{
		for(int i = 0; i < strlen(tokens); i++)
		{
			if(tokens[i] == '(')
			{
				counter++;
			}
			else if(tokens[i] == ')')
			{
				counter--;
			}
		}
		tokens = strtok(NULL,"\n");
	}
	if(counter != 0)
	{
		return 0;
	}
	return 1;
}

//Note: Current Implementation does not account for lines with multiple statements
int verifyAllLinesEndWithSemiColons(char* fileContents)
{
	char* tokens = strtok(fileContents,"\n");
	while(tokens != NULL)
	{
		if(tokens[strlen(tokens) - 1] != ';')
		{
			return 0;
		}
		tokens = strtok(NULL,"\n");
	}
	return 1;
}

int verifyAllLoopsEnd(char* fileContents)
{
	int counter = 0;
	char* tokens = strtok(fileContents,"\n");
	char forLoopState = 0;
	char whileLoopState = 0;
	char loopEndState = 0;

	while(tokens != NULL)
	{
		for(int i = 0; i < strlen(tokens); i++)
		{
			if(tokens[i] == 'f' && forLoopState == 0 && whileLoopState == 0 && loopEndState == 0)
			{
				forLoopState = 1;
			}
			else if(tokens[i] == 'o' && forLoopState == 1)
			{
				forLoopState = 2;
			}
			else if(tokens[i] == 'r' && forLoopState == 2)
			{
				forLoopState = 3;
			}
			else if(tokens[i] == '(' && forLoopState == 3)
			{
				counter++;
				forLoopState = 0;
			}
			else if(tokens[i] == ' ' && forLoopState == 3)
			{
				continue;
			}
			else if(tokens[i] == 'w' && whileLoopState == 0 && forLoopState == 0 && loopEndState == 0)
			{
				whileLoopState = 1;
			}
			else if(tokens[i] == 'h' && whileLoopState == 1)
			{
				whileLoopState = 2;
			}
			else if(tokens[i] == 'i' && whileLoopState == 2)
			{
				whileLoopState = 3;
			}
			else if(tokens[i] == 'l' && whileLoopState == 3)
			{
				whileLoopState = 4;
			}
			else if(tokens[i] == 'e' && whileLoopState == 4)
			{
				whileLoopState = 5;
			}
			else if(tokens[i] == '(' && whileLoopState == 5)
			{
				counter++;
				whileLoopState = 0;
			}
			else if(tokens[i] == ' ' && whileLoopState == 5)
			{
				continue;
			}
			else if(tokens[i] == 'e' && loopEndState == 0 && whileLoopState == 0 && forLoopState == 0)
			{
				loopEndState = 1;
			}
			else if(tokens[i] == 'n' && loopEndState == 1)
			{
				loopEndState = 2;
			}
			else if(tokens[i] == 'd' && loopEndState == 2)
			{
				loopEndState = 3;
			}
			else if(tokens[i] == 'l' && loopEndState == 3)
			{
				loopEndState = 4;
			}
			else if(tokens[i] == 'o' && loopEndState == 4)
			{
				loopEndState = 5;
			}
			else if(tokens[i] == 'o' && loopEndState == 5)
			{
				loopEndState = 6;
			}
			else if(tokens[i] == 'p' && loopEndState == 6)
			{
				loopEndState = 7;
			}
			else if(tokens[i] == ';' && loopEndState == 7)
			{
				counter--;
				loopEndState = 0;
			}
			else
			{
				forLoopState = 0;
				whileLoopState = 0;
				loopEndState = 0;
			}
		}
		tokens = strtok(NULL,"\n");
	}
	if(counter != 0)
	{
		return 0;
	}
	return 1;
}

int verifyAllIfStructuresEnd(char* fileContents)
{
	char* tokens = strtok(fileContents,"\n");
	char ifState = 0;
	char endIfState = 0;
	int counter = 0;
	while(tokens != NULL)
	{
		for(int i = 0; i < strlen(tokens); i++)
		{
			if(tokens[i] == 'i' && ifState == 0 && endIfState == 0)
			{
				ifState = 1;
			}
			else if(tokens[i] == 'f' && ifState == 1)
			{
				ifState = 2;
			}
			else if(tokens[i] == '(' && ifState == 2)
			{
				counter++;
				ifState = 0;
			}
			else if(tokens[i] == ' ' && ifState == 2)
			{
				continue;
			}
			else if(tokens[i] == 'e' && endIfState == 0 && ifState == 0)
			{
				endIfState = 1;
			}
			else if(tokens[i] == 'n' && endIfState == 1)
			{
				endIfState = 2;
			}
			else if(tokens[i] == 'd' && endIfState == 2)
			{
				endIfState = 3;
			}
			else if(tokens[i] == 'i' && endIfState == 3)
			{
				endIfState = 4;
			}
			else if(tokens[i] == 'f' && endIfState == 4)
			{
				endIfState = 5;
			}
			else if(tokens[i] == ';' && endIfState == 5)
			{
				counter--;
				endIfState = 0;
			}
			else
			{
				ifState = 0;
				endIfState = 0;
			}
		}	
		tokens = strtok(NULL,"\n");
	}
	if(counter != 0)
	{
		return 0;
	}
	return 1;
}

int verifyAllFunctionDefinitionsEnd(char* fileContents)
{
	char* tokens = strtok(fileContents,"\n");
	int counter = 0;
	char funcState = 0;
	char endFuncState = 0;
	while(tokens != NULL)
	{
		for(int i = 0; i < strlen(tokens); i++)
		{
			if(tokens[i] == 'f' && funcState == 0 && endFuncState == 0)
			{
				funcState = 1;
			}
			else if(tokens[i] == 'u' && funcState == 1)
			{
				funcState = 2;
			}
			else if(tokens[i] == 'n' && funcState == 2)
			{
				funcState = 3;
			}
			else if(tokens[i] == 'c' && funcState == 3)
			{
				funcState = 4;
			}
			else if(tokens[i] == 't' && funcState == 4)
			{
				funcState = 5;
			}
			else if(tokens[i] == 'i' && funcState == 5)
			{
				funcState = 6;
			}
			else if(tokens[i] == 'o' && funcState == 6)
			{
				funcState = 7;
			}
			else if(tokens[i] == 'n' && funcState == 7)
			{
				funcState = 8;
			}
			else if(tokens[i] == ' ' && funcState == 8)
			{
				counter++;
				funcState = 0;
			}
			else if(tokens[i] == 'e' && endFuncState == 0 && funcState == 0)
			{
				endFuncState = 1;
			}
			else if(tokens[i] == 'n' && endFuncState == 1)
			{
				endFuncState = 2;
			}
			else if(tokens[i] == 'd' && endFuncState == 2)
			{
				endFuncState = 3;
			}
			else if(tokens[i] == 'f' && endFuncState == 3)
			{
				endFuncState = 4;
			}
			else if(tokens[i] == 'u' && endFuncState == 4)
			{
				endFuncState = 5;
			}
			else if(tokens[i] == 'n' && endFuncState == 5)
			{
				endFuncState = 6;
			}
			else if(tokens[i] == 'c' && endFuncState == 6)
			{
				endFuncState = 7;
			}
			else if(tokens[i] == ';' && endFuncState == 7)
			{
				counter--;
				endFuncState = 0;
			}
			else
			{
				funcState = 0;
				endFuncState = 0;
			}
		}
		tokens = strtok(NULL,"\n");
	}
	if(counter != 0)
	{
		return 0;
	}
	return 1;
}
