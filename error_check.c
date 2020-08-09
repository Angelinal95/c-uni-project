#include "error_check.h"

void show_error(int num_er, int line_num)
{
    switch (num_er)
    {

    case 1:
        printf("line: %d, there's no such function", line_num);
        break;
    case 2:
        printf("line: %d,too many operands", line_num);
        break;
    case 3:
        printf("line: %d,too little operands", line_num);
        break;
    case 4:
        printf("line: %d,incorrect type of source operand ", line_num);
        break;
    case 5:
        printf("line: %d,incorrect type of destination operand", line_num);
        break;
    case 6:
        printf("line: %d,destination operand doesn't exist", line_num);
        break;
    case 7:
        printf("line: %d,source operand doesn't exist", line_num);
        break;
    case 8:
        printf("line: %d,incorrect structure of the statement", line_num);
        break;
    case 9:
        printf("line: %d,label already exists", line_num);
        break;
    case 10:
        printf("line: %d,labale's name is the same as the name of a saved word", line_num);
        break;
    case 11:
        printf("line: %d,there's a white space after the colon", line_num);
        break;
    case 12:
        printf("line: %d,missing quotation from a .string diractive statement", line_num);
        break;
    case 13:
        printf("line: %d,usage of an undifined label");
        break;
    case 14:
        printf("line: %d,label can't be a directive statement", line_num);
        break;
    case 15:
        printf("line: %d,label can't be an instruction", line_num);
        break;
    case 16:
        printf("line: %d,label is already defined as being external", line_num);
        break;
    /*case 17:
            printf("label is already defined as being internal");
            break;*/
    case 18:
        printf("line: %d,not a number", line_num);
        break;
    case 19:
        printf("line: %d,not a string", line_num);
        break;
    case 20:
        printf("line: %d,token's length is higher than %d", line_num, max_row_len);
        break;
    case 21:
        printf("line: %d,row too long(more than %d characters)", line_num, max_row_len);
        break;
    case 22:
        printf("line: %d,invalid adress", line_num);
        break;

    case 23:
        printf("line: %d, too many labels in the same row", line_num);
        break;

    case 24:
        printf("line: %d, too many opcodes in the same line", line_num);
        break;
    }
}