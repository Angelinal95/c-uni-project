#include "error_check.h"

void show_error(int num_er){
    switch(num_er){

        case 1:
            printf("there's no such function");
            break;
        case 2:
            printf("too many operands");
            break;
        case 3:
            printf("too little operands");
            break;
        case 4:
            printf("incorrect type of source operand ");
            break;
        case 5:
            printf("incorrect type of destination operand");
            break;
        case 6:
            printf("destination operand doesn't exist");
            break;
        case 7:
            printf("source operand doesn't exist");
            break;
        case 8:
            printf("incorrect structure of the statement");
            break;
        case 9:
            printf("label already exists");
            break;
        case 10:
            printf("labale's name is the same as the name of a saved word");
            break;
        case 11:
            printf("there's a white space after the colon");
            break;
        case 12:
            printf("missing quotation from a .string diractive statement");
            break;
        case 13:
            printf("usage of an undifined label");
            break;
        case 14:
            printf("label can't be a directive statement");
            break;
        case 15:
            printf("label can't be an instruction");
            break;
        case 16:
            printf("label is already defined as being external");
            break;
        /*case 17:
            printf("label is already defined as being internal");
            break;*/
        case 18:
            printf("not a number");
            break;
        case 19:
            printf("not a string");
            break;
        case 20:
            printf("token's length is higher than %d",row_len);
            break;
        case 21:
            printf("row too long(more than %d characters)",row_len);
            break;
        case 22:
            printf("invalid adress");
            break;



    }

}