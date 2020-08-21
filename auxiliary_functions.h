#include <stdio.h>
#include <string.h>

int count_spaces(char *); /*Count the spaces from the beginning of the string to the first character
                            and return the value of the count */
int isRegister(char *); /* If the variable is a valid register */

char modol16(int , char *,int );/* Converts an integer to a number at base 16, and puts the result into a string sent to the function */

char modol10(int ); /* count how much digits in the base 10 number  */

void writeInBase10(FILE *, int , int );/* Prints the number to the file in base 16 */

void writeInBase16(FILE *, int , int);/* Prints the number to the file in base 16 */

