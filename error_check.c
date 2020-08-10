#include "error_check.h"

void show_error(int num_er, int line_num)
{
    switch (num_er)
    {

    case 1:
        printf("line: %d, there's no such function\n\n", line_num);
        break;
    case 2:
        printf("line: %d,too many operands\n\n", line_num);
        break;
    case 3:
        printf("line: %d,too little operands\n\n", line_num);
        break;
    case 4:
        printf("line: %d,incorrect type of source operand\n\n", line_num);
        break;
    case 5:
        printf("line: %d,incorrect type of destination operand\n\n", line_num);
        break;
    case 6:
        printf("line: %d,destination operand doesn't exist\n\n", line_num);
        break;
    case 7:
        printf("line: %d,source operand doesn't exist\n\n", line_num);
        break;
    case 8:
        printf("line: %d,incorrect structure of the statement\n\n", line_num);
        break;
    case 9:
        printf("line: %d,label already exists\n\n", line_num);
        break;
    case 10:
        printf("line: %d,labale's name is the same as the name of a saved word\n\n", line_num);
        break;
    case 11:
        printf("line: %d,there's a white space after the colon\n\n", line_num);
        break;
    case 12:
        printf("line: %d,missing quotation from a .string diractive statement\n\n", line_num);
        break;
    case 13:
        printf("line: %d,usage of an undifined label\n\n");
        break;
    case 14:
        printf("line: %d,label can't be a directive statement\n\n", line_num);
        break;
    case 15:
        printf("line: %d,label can't be an instruction\n\n", line_num);
        break;
    case 16:
        printf("line: %d,label is already defined as being external\n\n", line_num);
        break;
    /*case 17:
            printf("label is already defined as being internal");
            break;*/
    case 18:
        printf("line: %d,not a number\n\n", line_num);
        break;
    case 19:
        printf("line: %d,not a string\n\n", line_num);
        break;
    case 20:
        printf("line: %d,token's length is higher than %d\n\n", line_num, max_row_len);
        break;
    case 21:
        printf("line: %d,row too long(more than %d characters)\n\n", line_num, max_row_len);
        break;
    case 22:
        printf("line: %d,invalid adress\n\n", line_num);
        break;

    case 23:
        printf("line: %d, too many labels in the same row\n\n", line_num);
        break;

    case 24:
        printf("line: %d, too many opcodes in the same line\n\n", line_num);
        break;
    case 25: 
        printf("line: %d, not a valid register\n\n", line_num);
        break;
    }

}

int valid_number(char *checkNum, int line)
{
    int i, true=1, false=0;

    if(checkNum == NULL)
    {
        printf("No variable of type number was obtained for the function\n");
        return false;
    }

    else if((checkNum[0] == '#') || (checkNum[0] == '-') || (checkNum[0] == '+') || ((checkNum[0] >= '0' )&& (checkNum[0] <= '9')))
    {
        for(i=1; i <= strlen(checkNum); i++)
        {
            if((checkNum[i] < '0') || (checkNum[i] > '9'))
            {
                show_error(notNumber, line);
                return false; /*error*/
            }  
        }
        return true; /* is a valid number*/
    }
    else
    {
        return false; /* checkNum[0] is not '#' , not a number and not '-' or '+' */
    }
}

int valid_register(char *reg, int line)
{
    int i, true=1, false=0;

    if (reg == NULL)
    {
        printf("No register variable was obtained for the function.\n");
        return false;
    }
    else if ((reg[0] != 'r' ) || (reg[1] < '0')||(reg[1] > '7') || (strlen(reg) > 2))
    {
        show_error(notValidRegister, line);
        return false;
    }
    return true;
}

int check_extern_label(char *label, int line)
{
    return 0;
}

int check_entry_label(char *label, int line)
{
    return 0;
}

int check_adress(char *adress, int line)
{
    return 0;
}

int name_function(char *nameFunc, int line)
{
    return 0;
}

int valid_variable(char *var, int line)
{
    return 0;
}

int valid_directive(char *directive, int line)
{
    return 0;
}

int valid_data(char *data, int line)
{
    return 0;
}

int valid_string(char *string, int line)
{
    return 0;
}

int defined_label(char *label, int line)
{
    return 0;
}

int valid_label(char *label, int line)
{
    return 0;
}
