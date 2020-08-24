#include <stdlib.h>
#include "file_functions.h"



/* Create a new file by selecting a name and extension */
FILE *createNewFile(char *fileName, char *fileType)
{
	FILE *file;
	 
	char *fullFileName = (char *)malloc(strlen(fileName) + strlen(fileType) + 1);
    if (!fullFileName)
    {
        return NULL;
    }

    fullFileName = strcpy(fullFileName, fileName);
    fullFileName = strcat(fullFileName, fileType);

	file = fopen(fullFileName, "a");
	free(fullFileName);

	return file;
}


/* create object file, contains the assembly lines in base 16 */
void ObjectFile(char *fileName,int IC, int DC,int *instrucLinesArr, struct symbols_table *dataArr)
{
	int i, val;
	FILE *file;
	file = createNewFile(fileName, ".ob");

	/* write IC into the file */
	
	fprintf(file, "%d\t\t", ((INITIAL_ADDRESS - IC - DC) + 1)); // print the num of lines in the assembly code

    /* write DC into the file */
    fprintf(file, "%d\n", DC);

	/* Print all the code line */
	for (i = 0; i < (IC - DC); i++)
	{
		writeInBase10(file, INITIAL_ADDRESS + i, 6);
		fprintf(file, "\t\t");
		writeInBase16(file, instrucLinesArr[i], 6);
        fprintf(file, "\n");

	}

	fclose(file);
}


/* creates the entry file, contains the addresses of entry labels in base 10 */
void EntriesFile(char *fileName, int *numOfEntries, struct symbols_table *symbolList)
{
	FILE *file;
	struct symbols_table *tempLabel = symbolList;

	
	if (tempLabel->label)// if there are entry labels 
	{	

		file = createNewFile(fileName, ".ent");

		do 
		{
			if (!strcmp(tempLabel->type_of_symbol,"entry"))// check if the label type is entry
			{
				fprintf(file, "%s\t\t", tempLabel->label);
				writeInBase10(file, tempLabel->address, 6);
				fprintf(file, "\n");
			}

			tempLabel = tempLabel->next; //pass to the next label

		} while (tempLabel->label); // stop while no more entry label

		fclose(file);

	}

}


/* creates the extern file, contains the addresses for the extern labels in base 10 */
void ExternFile(char *fileName, struct symbols_table *tempLabel, int *numOfExtern)
{
	FILE *file;

	/* if there are extern labels */
	if (*numOfExtern)
	{	

		file = createNewFile(fileName, ".ext");

		do 
		{
			if (!strcmp(tempLabel->type_of_symbol,"extern"))// check if the label type is extern
			{
				fprintf(file, "%s\t\t", tempLabel->label);
				writeInBase10(file, tempLabel->address, 6);
				fprintf(file, "\n");
			}

			tempLabel = (tempLabel->next); //pass to the next label

		} while (tempLabel->label); // stop while the next is Null.

		fclose(file);

	}

}









