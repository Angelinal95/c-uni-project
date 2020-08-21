#include "file_functions.h"


/* Create a new file by selecting a name and extension */
FILE *openFile(char *fileName, char *fileType)
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


/* create object file, contains the assembly lines in base 16. */
void createObjectFile(char *fileName,int *instrucLinesArr, int IC, int DC)
{
	int i;
	FILE *file;
	file = openFile(fileName, ".ob");

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