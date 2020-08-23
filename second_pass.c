#include "MAIN.h"
#include "error_check.h"

typedef enum {A = 4, R = 2, E = 1} val_A_R_E;


typedef struct
{
    char *func_name;
    int func_num;
    int op_code;
} func_table;

func_table func_table_1[] = {
    {"mov", NULL, 0}, {"cmp", NULL, 1}, {"add", 1, 2}, {"sub", 2, 2}, {"lea", NULL, 4}, {"clr", 1, 5}, {"not", 2, 5}, {"inc", 3, 5}, {"dec", 4, 5}, {"jmp", 1, 9}, {"bne", 2, 9}, {"jsr", 3, 9}, {"red", NULL, 12}, {"prn", NULL, "13"}, {"rts", NULL, 14}, {"stop", NULL, 15}

};

void completeLabelAddress(int IC) 
{
    symbols_table *tempLabel = symbols_list;

	/* Search in the array for .entry / .data / .string label */
	while (tempLabel)
    {    
		if (!strcmp(tempLabel->type_of_symbol,"entry"))
        {
            if (!tempLabel->address)
            {
			    /* Increase the address */
			    tempLabel->address += INITIAL_ADDRESS + IC;
            }
		}
        else if (!strcmp(tempLabel->type_of_symbol,"data") || !(tempLabel->type_of_symbol,"string"))
        {
			/* Increase the address */
			tempLabel->address += INITIAL_ADDRESS + IC;
		}

        tempLabel = tempLabel->next;
    }

}


/* check if there is an illegal entry label */
int countIllegalEntries() 
{
	int errorFlag = 0 ;
	symbols_table *entryLabel = entryLabelsList;
    symbols_table *labelToComper = symbols_list;

	while (entryLabel) 
    {
        if(!defined_label(entryLabel->label, entryLabel->line))
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
			        if (!strcmp(labelToComper->type_of_symbol, "exstern")) 
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

int entryLabelAlreadyInList(char *entryLabelName) 
{
    symbols_table *tempEntryLabel = symbols_list;

	while (tempEntryLabel) 
    {
		if (!strcmp(entryLabelName, tempEntryLabel->label))
        {
			return TRUE;
		}

        tempEntryLabel = tempEntryLabel->next;
	}
	return FALSE;
}


/* if label exist return pointer to the label in symbols_table ,or NULL if label not found. */
 symbols_table *searchLabel(char *labelName) 
 {
	symbols_table *tempLabel = symbols_list;

	
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


/* If operand is a label, update the value to be the address of the label. */
int ifOpIsLabel(operand *op, int lineNum) 
{
    symbols_table *label = NULL;

	if (op->Addressing_Mode == 1) 
    {
		label = searchLabel(op->operand_value);

		/* Check if label != NULL */
		if (!label) 
        {
            show_error(undifinedLabel, line_num);
            return FALSE;
		}

		op->operand_value = label->address;
	}

	return TRUE;
}

/* Returns the int value of a memory word. */
int returnIntMemoryWord(memWordCode memory) 
{

	unsigned int intBitMask = ~0;
	intBitMask >>= ((sizeof(int) * ONE_BYTE_SIZE) - ONE_WORD_SIZE);/* int of '1' in all 24 first bits, all the rest bits '0' */

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

    return (int) op.Addressing_Mode; // else , operand type == (0 or 1 or 2 or 3) return the number in Addressing_Mode
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



memWordCode lineMemoryWord(command_line line) 
{
	memWordCode memory = { 0 };
    symbols_table *label = NULL;

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

    label = searchLabel(line.label);

    if (label != NULL)
    {
        if (symbols_list->type_of_symbol == "external" || symbols_list->value == '0')
        {
            memory.A_R_E = E;
            memory.wordVal.number = 0;
        }
        else
        {
            memory.A_R_E = R;
            memory.wordVal.number = label->address ;
        }
        
    }
    memory.wordVal.number = command_line_list->;

	return memory;
}



void addWordToMemory(int *memoryWordArr, int *memCoun, memWordCode memory) {
	
	if (*memCoun < ((IC+DC)-INITIAL_ADDRESS)) //There is space in the array
    {
		
		memoryWordArr[(*memCoun)++] = returnIntMemoryWord(memory);// Add the memory word
	}
}



void pushdataToMemory(int *wordMemoryArr, int *memCount, int DC) 
{
	int i;
	unsigned int intBitMask = ~0;

	intBitMask >>= ((sizeof(int) * ONE_BYTE_SIZE) - ONE_WORD_SIZE);/* int of '1' in all 24 first bits, all the rest bits '0' */

	for (i = 0; i < DC; i++) //Add each int from g_dataArr to the end of memoryArr 
    { 
		if (*wordMemoryArr) {
			
			wordMemoryArr[(*memCount)++] = intBitMask & g_dataArr[i];// makes sure we only use the first bits 
		} 
        else //dont have  more space in wordMemoryArr
        {
			return;
		}
	}
}


/* Reads second time. */
/* It converts all the lines into the memory. */
int second_pass(int* wordMemoryArr, command_line *arrLines, int lineNum, int IC, int DC) 
{
	 int error, memCount = 0, i;

	
	updateDataLabelsAddress(IC); // update the operand if it label 

	
	error += countIllegalEntries(); // Check for illegal entries 

	
	for (i = 0; i < lineNum; i++) // Add line in to the memory
    {
		if (!addLineToMemory(wordMemoryArr, &memCount, (arrLines + i))) // if found error while adding line to memory 
        {
			error++;
		}
	}
	
	addDataToMemory(wordMemoryArr, &memCount, DC);// Add data to the end of memory

    return error;
}








