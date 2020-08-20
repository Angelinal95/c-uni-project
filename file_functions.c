#include "file_functions.h"


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