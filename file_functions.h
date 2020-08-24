#include "MAIN.h"
#include "auxiliary_functions.h"

FILE *createNewFile(char *fileName, char *fileType);/* Creates a file for writing from a given file name and file type,returns a pointer. */

void ObjectFile(char *fileName,int IC, int DC,int *instrucLinesArr, symbols_table *dataArr);

void EntriesFile(char *fileName, int *numOfEntries, symbols_table *symbolList);

void ExternFile(char *fileName, symbols_table *tempLabel, int *numOfExtern);

