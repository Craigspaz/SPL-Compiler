#ifndef TRANSLATE_H
#define TRANSLATE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* translateIfAndLoops(char* fileContents);

char* translateVariables(char* fileContents);

char* translateFunctions(char* fileContents);

char* translatePointersAndOperators(char* fileContents);

#endif
