#include "MAIN.h"
#include "auxiliary_functions.h"

FILE *createNewFile(char *fileName, char *fileType);/* Creates a file for writing from a given file name and file type,returns a pointer. */

void ObjectFile(char *fileName, int *instrucLinesArr, int IC, int DC);

void EntryFile(char *fileName);

void ExternFile(char *fileName);

