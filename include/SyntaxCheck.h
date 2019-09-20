#ifndef SYNTAXCHECK_H
#define SYNTAXCHECK_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int verifySyntax(char* fileContents);

int verifyAllParenthesesEnd(char* fileContents);

int verifyAllLinesEndWithSemiColons(char* fileContents);

int verifyAllLoopsEnd(char* fileContents);

int verifyAllIfStructuresEnd(char* fileContents);

int verifyAllFunctionDefinitionsEnd(char* fileContents);

#endif
