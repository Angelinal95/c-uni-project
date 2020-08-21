#include <stdio.h>
#include <string.h>

int count_spaces(char *); /*Count the spaces from the beginning of the string to the first character
                            and return the value of the count */
int isRegister(char *); /* If the variable is a valid register */

char modol16(int num, char *arrNum,int arrLength);/* Converts an integer to a number at base 16, and puts the result into a string sent to the function */


void printInBase16(FILE *, int , int);/* Prints the number to the file in base 16 */

