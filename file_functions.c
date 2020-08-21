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
	writeInBase16(file, IC, 1);
	fprintf(file, "\t\t");

    /* write DC into the file */
	writeInBase16(file, DC, 1);

	/* Print all of memoryArr */
	for (i = 0; i < IC + DC; i++)
	{
		fprintf(file, "\n");
		writeInBase16(file, INITIAL_ADDRESS + i, 3);
		fprintf(file, "\t\t");
		writeInBase16(file, instrucLinesArr[i], 3);
	}

	fclose(file);
}