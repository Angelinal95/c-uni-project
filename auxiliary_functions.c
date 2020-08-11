#include <stdio.h>

int count_spaces(char *string)
{
    int counter = 0, i;

    if (string == NULL)
    {
        return 0;
    }

    for(i=0; string[i] == ' '; i++)//Count the spaces from the beginning of the string to the first character.
    {
        counter++ ;
    }
    
    return counter;
    
}
