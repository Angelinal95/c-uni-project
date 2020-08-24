#include "MAIN.h"
#include "error_check.h"

typedef enum {A = 4, R = 2, E = 1} val_A_R_E;


void completeLabelAddress(int IC,int DC, symbols_table *EntryTemp, symbols_table *dataTable,symbols_table *tempLabel) 
{
    int i = 0;

	/* Search in the array for .entry / .data / .string label */
	while (tempLabel)
    {    
		if (!strcmp(tempLabel->type_of_symbol,"entry"))
        {
            if (!tempLabel->address)
            {
			    /* Increase the address */
			    EntryTemp->address = tempLabel->address;
                EntryTemp->label = tempLabel->label;
                EntryTemp = EntryTemp->next;
            }

		}
        else if (!strcmp(tempLabel->type_of_symbol,"data") || !(tempLabel->type_of_symbol,"string"))
        {
			/* Increase the address */
            dataTable->value = tempLabel->value;
            dataTable->address = tempLabel->L + IC;
            if (i < DC)
            {
                dataTable = (dataTable + i);
                i++;
            }
            
		}

        tempLabel = tempLabel->next;
    }

}


/* check if there is an illegal entry label */
int countIllegalEntries(symbols_table *entryLabel, int *numOfEntries) 
{
	int errorFlag = 0 ;
    symbols_table *labelToComper = symbols_list;

	while (entryLabel->label) 
    {
        if(!defined_label(entryLabel->label, symbols_list))
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


memWordCode lineMemWordCode(command_line line) 
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
            return memory;
        }
        else
        {
            memory.A_R_E = R;
            memory.wordVal.number = label->address ;
            return memory;
        }
        
    }
    else
    {
        memory.A_R_E = R;
        memory.wordVal.number = command_line_list->operand_src->operand_value;
    }

	return memory;
}



void addWordToMemory(int *wordMemoryArr, int *memCount, memWordCode memory) {
	
	if (*memCount < ((IC+DC)-INITIAL_ADDRESS)) //There is space in the array
    {
		
		*(wordMemoryArr + (*memCount)) = returnIntMemoryWord(memory);// Add the memory word
        *(memCount)++;
	}
}



void pushdataToMemory(symbols_table *dataTable ,int *wordMemoryArr, int *memCount, int DC) 
{
	int i, val;
	unsigned int intBitMask = ~0;
    

	intBitMask >>= ((sizeof(int) * ONE_BYTE_SIZE) - ONE_WORD_SIZE);/* int of '1' in all 24 first bits, all the rest bits '0' */

	for (i = 0; i < DC; i++) //Add each int from dataArr to the end of memoryArr 
    { 
        if (!strcmp(instruction_line_list->type_of_inst, "external"))// if external pass
        {
            continue;
        }
        val = atoi(dataTable->value);
		*(wordMemoryArr + (*memCount)) = intBitMask & val;// makes sure we only use the first bits 
        *(memCount)++;	
        
	}

}


/* Reads second time. */
/* It converts all the lines into the memory. */
void second_pass(int *wordMemoryArr, symbols_table *entryLabelList, symbols_table *dataTable, int *numOfEntries, int IC, int DC) 
{
    wordMemoryArr = (int*)malloc(sizeof(int) * (IC+DC-INITIAL_ADDRESS));
	int error, memCount = 0, i;
    command_line *line = command_line_list;
    memWordCode memory;
    symbols_table *LabelList = symbols_list;
    symbols_table *dataTable = (symbols_table *)malloc(sizeof(symbols_table)*DC);
	
    completeLabelAddress(IC, DC, entryLabelList, dataTable, LabelList); // update the operand if it label 

	error += countIllegalEntries(entryLabelList, numOfEntries); // Check for illegal entries 

	
	for (i = 0; i < (IC+DC-INITIAL_ADDRESS); i++) // Add line in to the memory
    {

		memory = lineMemWordCode(*line);
        addWordToMemory(wordMemoryArr, &memCount, memory);
       
	}
	
	pushdataToMemory(dataTable, wordMemoryArr, &memCount, DC);// Add data to the end of memory

    
}








