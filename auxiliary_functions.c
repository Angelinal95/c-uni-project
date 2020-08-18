
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
