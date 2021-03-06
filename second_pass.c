
#include "error_check.h"

typedef enum
{
    A = 4,
    R = 2,
    E = 1
} val_A_R_E;

void completeLabelAddress(int IC, int DC, struct symbols_table *EntryTemp, struct symbols_table *dataTable, struct symbols_table *tempLabel, int *numOfEntries, struct instruction_line *instruction_line_list)
{
    int i = 0;

    /* Search in the array for .entry / .data / .string label */
    while (tempLabel)
    {
        if (!strcmp(tempLabel->type_of_symbol, "entry"))
        {
            if (!tempLabel->address)
            {
                /* Increase the address */
                EntryTemp->address = tempLabel->address;
                EntryTemp->label = tempLabel->label;
                EntryTemp->next = (struct symbols_table *)malloc(sizeof(struct symbols_table));
                EntryTemp = EntryTemp->next;
                (*numOfEntries)++;
            }
        }
        else if (!strcmp(tempLabel->type_of_symbol, "data") || !(tempLabel->type_of_symbol, "string"))
        {
            /* Increase the address */
            tempLabel->address = tempLabel->L + IC;
            while (tempLabel->value)
            {

                dataTable->value = tempLabel->value;
                dataTable->address = tempLabel->L + IC;
                tempLabel->value++;

                if (i < DC)
                {
                    dataTable = (dataTable + i);
                    i++;
                }
                else
                    return;
            }
        }

        tempLabel = tempLabel->next;
    }
    while (instruction_line_list)
    {
        if (instruction_line_list->label == NULL)
        {
            while (instruction_line_list->info)
            {

                dataTable->value = instruction_line_list->info;
                instruction_line_list->info++;

                if (i < DC)
                {
                    dataTable = (dataTable + i);
                    i++;
                }
                else
                    return;
            }
        }
    }
}

/* check if there is an illegal entry label */
int countIllegalEntries(struct symbols_table *entryLabel, int *numOfEntries, struct symbols_table *LabelList)
{
    int errorFlag = 0;
    struct symbols_table *labelToComper = LabelList;

    while (entryLabel->label)
    {
        if (!defined_label(entryLabel->label, LabelList))
        {
            show_error(undifinedLabel, entryLabel->line);
            errorFlag++;
        }
        else
        {

            while (labelToComper)
            {
                if (!strcmp(entryLabel->label, labelToComper->label))
                {
                    (*numOfEntries)++; // count the entry labels

                    if (!strcmp(labelToComper->type_of_symbol, "exsternal"))
                    {
                        printError("error in line: %d The parameter .entry can't be external label.", entryLabel->line);
                        errorFlag++;
                    }
                }

                labelToComper = labelToComper->next;
            }
        }

        entryLabel = entryLabel->next;
    }
    return errorFlag;
}

/* if label exist return pointer to the label in symbols_table ,or NULL if label not found. */
struct symbols_table *searchLabel(char *labelName, struct symbols_table *LabelList)
{
    struct symbols_table *tempLabel = LabelList;

    while (tempLabel)
    {
        if (!strcmp(labelName, tempLabel->label))
        {
            return tempLabel;
        }

        tempLabel = tempLabel->next;
    }

    return NULL;
}

/* Returns the int value of a memory word. */
int returnIntMemoryWord(memWordCode memory)
{

    unsigned int intBitMask = ~0;
    intBitMask >>= ((sizeof(int) * ONE_BYTE_SIZE) - ONE_WORD_SIZE); /* int of '1' in all 24 first bits, all the rest bits '0' */

    /* make only 24 bits to use */
    intBitMask = intBitMask & ((memory.wordVal.number << 3) + memory.A_R_E);
    return intBitMask;
}

/* return the addressing_Mode of the operand */
int returnModeOpType(operand op)
{

    if (op.Addressing_Mode == NULL) //if operand type == NULL return 0;
    {
        return 0;
    }

    return (int)op.Addressing_Mode; // else , operand type == (0 or 1 or 2 or 3) return the number in Addressing_Mode
}

int regNum(operand op)
{
    int numOP;

    if (op.operand_value == NULL) //if operand == NULL return 0;
    {
        return 0;
    }
    for (numOP = 0; numOP < 8; numOP++)
    {
        if ((int)op.operand_value == numOP)
        {
            return numOP;
        }
    }
    return 0;
}

memWordCode lineMemWordCode(struct command_line line, struct symbols_table *LabelList)
{
    memWordCode memory = {0};
    struct symbols_table *Tlabel = NULL;

    if ((line.operand_dest != NULL) && (line.operand_src != NULL))
    {
        memory.A_R_E = A; /* absolute */
                          /* fills the bits inside the word memory */
        memory.wordVal.instructionBits.funct = line.cmd->funct;
        memory.wordVal.instructionBits.opcode = line.cmd->opcode;
        memory.wordVal.instructionBits.regSrc = regNum(*line.operand_src);
        memory.wordVal.instructionBits.regDest = regNum(*line.operand_dest);
        memory.wordVal.instructionBits.modeSrc = returnModeOpType(*line.operand_src);
        memory.wordVal.instructionBits.modeDest = returnModeOpType(*line.operand_dest);
        return memory;
    }

    Tlabel = searchLabel(line.label, LabelList);

    if (Tlabel != NULL)
    {
        if (LabelList->type_of_symbol == "external" || LabelList->value == '0')
        {
            memory.A_R_E = E;
            memory.wordVal.number = 0;
            return memory;
        }
        else
        {
            memory.A_R_E = R;
            memory.wordVal.number = Tlabel->address;
            return memory;
        }
    }
    else
    {
        memory.A_R_E = R;
        memory.wordVal.number = line.operand_src->operand_value;
    }

    return memory;
}

void addWordToMemory(int *wordMemoryArr, int *memCount, memWordCode memory, int IC, int DC)
{

    if (*memCount < ((IC + DC) - INITIAL_ADDRESS)) //There is space in the array
    {

        *(wordMemoryArr + (*memCount)) = returnIntMemoryWord(memory); // Add the memory word
        *(memCount)++;
    }
}

void pushdataToMemory(struct symbols_table *dataTable, int *wordMemoryArr, int *memCount, int DC)
{
    int i, val;
    unsigned int intBitMask = ~0;

    intBitMask >>= ((sizeof(int) * ONE_BYTE_SIZE) - ONE_WORD_SIZE); /* int of '1' in all 24 first bits, all the rest bits '0' */

    for (i = 0; i < DC; i++) //Add from dataTable to the end of memoryArr
    {

        val = atoi(dataTable->value);
        *(wordMemoryArr + (*memCount)) = intBitMask & val; // makes sure we only use the first bits
        dataTable++;
        (*memCount)++;
    }
}

/* Reads second time. */
/* It converts all the lines into the memory. */
void second_pass(char *fileName, int IC, int DC, int error, struct symbols_table *LabelList, struct command_line *comLine, struct instruction_line *instruction_line_list)
{
    int *wordMemoryArr;                                                                               //for the second pass to print the output files
    int i;                                                                                            //use in second read
    int numOfEntries = 0;                                                                             //use in second read
    struct symbols_table *entryLabels = (struct symbols_table *)malloc(sizeof(struct symbols_table)); //use in second read
    struct symbols_table *dataArr;                                                                    //use in the second read
    int memCount = 0;
    memWordCode memory;
    struct symbols_table *dataTable = (struct symbols_table *)malloc(sizeof(struct symbols_table) * DC);
    wordMemoryArr = (int *)malloc(sizeof(int) * (IC + DC - INITIAL_ADDRESS));

    completeLabelAddress(IC, DC, entryLabels, dataTable, LabelList, &numOfEntries, instruction_line_list); // update the operand if it label

    error += countIllegalEntries(entryLabels, &numOfEntries, LabelList); // Check for illegal entries

    for (i = 0; i < (IC + DC - INITIAL_ADDRESS); i++) // Add line in to the memory
    {

        memory = lineMemWordCode(*comLine, LabelList);
        addWordToMemory(wordMemoryArr, &memCount, memory, IC, DC);
    }

    pushdataToMemory(dataTable, wordMemoryArr, &memCount, DC); // Add data to the end of memory

    /* If there are no errors */
    if (!error) // If no errors, do the print to the files
    {
        /* Create all the output files */
        ObjectFile(fileName, IC, DC, wordMemoryArr, dataArr);
        ExternFile(fileName, LabelList /*, linesArr, numOflines*/);
        EntriesFile(fileName, numOfEntries);
        printf("success, output files for \"%s.as\" created.\n", fileName);
    }
}
