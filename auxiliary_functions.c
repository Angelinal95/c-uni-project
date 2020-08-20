
#include "MAIN.h"
#include "auxiliary_functions.h"


int count_spaces(char *string)
{
    int counter = 0, i;

    for (i = 0; string[i] == ' '; i++) //Count the spaces from the beginning of the string to the first character.
    {
        counter++;
    }

    return counter;
}

int isRegister(char *reg) //check if register (return : 0 if No or 1 if Yes)
{
    if ((reg[0] != 'r' ) || (reg[1] < '0')||(reg[1] > '7') || (strlen(reg) > 2))
    {
        return 0; //not register
    }
    return 1; //is register
}
int modol2(int num, int *binariArrNum,int numOfBits)
{

    if (num < 2)
    {
        return num;  
    }
    
    binariArrNum[numOfBits-1] = modol2(num / 2, binariArrNum, numOfBits-1); 
    return num%2;
}

void intToBinari(int *bitFields, int numOfBits, int numOfLines)
{
    int i,j;
    int *arrBinariNum = (int *)malloc(sizeof(int)*numOfBits);

    for (i=0; i <= numOfLines; i++)
    {
        modol2(*bitFields, arrBinariNum, numOfBits);
        for (j=0; j < numOfBits; j++)
        {
            *(bitFields+j) = *(arrBinariNum+j);
        }   
    } 
}

/*void trunsInstrucToBinari(full_instruction *instructin, int numOfLines)
{
    int i;

    for (i=0; i < numOfLines; i++)
    {
        instructin->opcode
    }
}*/


