
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

/* Converts an integer to a number at base 16, and puts the result into a string sent to the function */
char modol16(int num, char *arrNum, int arrLength)
{
    char listBase16[] = "0123456789ABCDEF";

    if (num < 16)
    {
        return listBase16[num % 16];  
    }
    
    arrNum[arrLength-1] = modol16(num / 16, arrNum, arrLength-1); 
    return listBase16[num%16];
}

/* Prints the number to the file in base 16 */
void printInBase16(FILE *file, int instuction, int wordMemLength)
{
    int j, sumOfZiros;
    char base16num[7]={0}; //Space saver: \ 0

    modol16(instuction, base16num, wordMemLength);

    if(sumOfZiros = (wordMemLength - strlen(base16num)))//If the string is shorter than 6 characters
    {
        for(j=0; j<sumOfZiros; j++)//Completes with '0' so that it contains 6 numbers in print
        {
            fprintf(file, "0");
        }
    }
    fprintf(file, "%s \n", base16num);
     
}



