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
void ObjectFile(char *fileName,int *instrucLinesArr, int IC, int DC)
{
	int i;
	FILE *file;
	file = createNewFile(fileName, ".ob");

	/* write IC into the file */
	
	fprintf(file, "%d\t\t", IC);

    /* write DC into the file */
    fprintf(file, "%d\n", DC);

	/* Print all of memoryArr */
	for (i = 0; i < IC + DC; i++)
	{
        
		writeInBase10(file, INITIAL_ADDRESS + i, 6);
		fprintf(file, "\t\t");
		writeInBase16(file, instrucLinesArr[i], 6);
        fprintf(file, "\n");

	}

	fclose(file);
}


/* creates the entry file, contains the addresses of entry labels in base 10 */
void EntriesFile(char *fileName)
{
	FILE *file;
	symbols_table *tempLabel = labelList;

	/* if there are entry labels */
	if (g_numOfEntries)
	{	

		file = createNewFile(fileName, ".ent");

		do 
		{
			if (!strcmp(tempLabel->type_of_symbol,"entry"))// check if the label type is entry
			{
				fprintf(file, "%s\t\t", tempLabel->label);
				writeInBase10(file, tempLabel->value, 6);
				fprintf(file, "\n");
			}

			tempLabel = tempLabel->next; //pass to the next label

		} while (tempLabel); // stop while the next is Null.

		fclose(file);

	}

}


/* creates the extern file, contains the addresses for the extern labels in base 10 */
void ExternFile(char *fileName)
{
	FILE *file;
	symbols_table *tempLabel = labelList;

	/* if there are extern labels */
	if (g_numOfExterns)
	{	

		file = createNewFile(fileName, ".ext");

		do 
		{
			if (!strcmp(tempLabel->type_of_symbol,"extern"))// check if the label type is extern
			{
				fprintf(file, "%s\t\t", tempLabel->label);
				writeInBase10(file, tempLabel->value, 6);
				fprintf(file, "\n");
			}

			tempLabel = (tempLabel->next); //pass to the next label

		} while (tempLabel); // stop while the next is Null.

		fclose(file);

	}

}









