#include "Launch.h"
#include <string.h>

char* readFile(FILE* file)
{
	if(file == NULL)
	{
		fprintf(stderr, "ERROR: File is not valid!\n");
		exit(1);
	}

	char* contentsOfFile = malloc(1024 * 30 * sizeof(char)); //Estimate that there are 1024 characters per line and there are 30 lines. This can be expaned if needed later.
	
	if(contentsOfFile == NULL)
	{
		fprintf(stderr, "ERROR: Not Enough Memory!\n");
		exit(1);
	}
	char line[1024];
	while(fgets(line,1024,file))
	{
		if(strlen(contentsOfFile) >= 1024*28*sizeof(char))
		{
			contentsOfFile = realloc(contentsOfFile,strlen(contentsOfFile)*sizeof(char) * 30);
			if(contentsOfFile == NULL)
			{
				fprintf(stderr, "ERROR: Not Enough Memory!\n");
				exit(1);
			}
		}
		strcat(contentsOfFile,line);
	}
	return contentsOfFile;
}



int main(int argc, char** argv)
{

	FILE* inputFile = NULL;
	FILE* outputFile = NULL;
	if(argc > 1)
	{
		printf("Getting filename from commandline\n");
		char* inputFilePath = argv[1];
		inputFile = fopen(inputFilePath,"r");
		strcat(inputFilePath,".c");
		outputFile = fopen(inputFilePath,"w");
	}
	else
	{
		printf("Getting filename from user in terminal\nWhat is the input file path?\n");
		char filename[253];
		fgets(filename,253,stdin);
		char* inputToken = strtok(filename,"\n");
		inputFile = fopen(&inputToken[0],"r");\
		filename[strlen(filename) + 1] = '.';
		filename[strlen(filename) + 2] = 'c';
		filename[strlen(filename) + 3] = '\0';
		outputFile = fopen(filename,"w");
	}

	if(inputFile == NULL)
	{
		fprintf(stderr, "ERROR: Input file is not valid!\n");
		exit(1);
	}
	if(outputFile == NULL)
	{
		fprintf(stderr, "ERROR: Output file is not valid!\n");
		exit(1);
	}

	printf("Checked Files...\n");
	char* fileToCompile = readFile(inputFile);

	char* copyOfFileToCompile = malloc(strlen(fileToCompile) + 1);
	if(copyOfFileToCompile == NULL)
	{
		fprintf(stderr, "ERROR: Not enough memory!");
		exit(1);
	}
	strcpy(copyOfFileToCompile,fileToCompile);
	
	printf("Checking syntax...\n");
	//Check Syntax
	if(verifySyntax(fileToCompile))
	{
		printf("Syntax is correct...\n");
	}
	//Translate to C
	
	//Test Translate
	char* test = translateIfAndLoops(copyOfFileToCompile);
	printf("Finished Translating If and Loops...\n");
	char* test1 = translateVariables(test);
	printf("Finished Translating Variables...\n");
	char* test2 = translateFunctions(test1);
	printf("Finished Translating Functions...\n");
	char* test3 = translatePointersAndOperators(test2);
	printf("Finished Translating Pointers and Operators...\n");
	fprintf(outputFile,"%s","#include <stdio.h>\n int main(){");
	fprintf(outputFile,"%s",test3);
	fprintf(outputFile,"%s","return 0;}");
	printf("Translated Code:\n %s\nEnd Of Translated Code\n",test3);

	//Run through C compiler

	fclose(inputFile);
	fclose(outputFile);
	free(test);
	free(copyOfFileToCompile);
	free(fileToCompile);
	return 0;
}
