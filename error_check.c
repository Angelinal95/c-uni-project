#include "error_check.h"

void show_error(int num_er, int line_num)
{
    switch (num_er)
    {

    case function:
        printf("line: %d, there's no such function\n\n", line_num);
        break;

    case manyOperands:
        printf("line: %d,too many operands\n\n", line_num);
        break;

    case littleOperands:
        printf("line: %d,too little operands\n\n", line_num);
        break;

    case typeOperand:
        printf("line: %d,incorrect type of source operand\n\n", line_num);
        break;

    case typeDestination:
        printf("line: %d,incorrect type of destination operand\n\n", line_num);
        break;

    case destinationNotFound:
        printf("line: %d,destination operand doesn't exist\n\n", line_num);
        break;

    case sourceNotFound:
        printf("line: %d,source operand doesn't exist\n\n", line_num);
        break;

    case incorrectStatement:
        printf("line: %d,incorrect structure of the statement\n\n", line_num);
        break;

    case labelExists:
        printf("line: %d,label already exists\n\n", line_num);
        break;

    case savedWord:
        printf("line: %d,labale's name is the same as the name of a saved word\n\n", line_num);
        break;

    case whiteSpace:
        printf("line: %d,there's a white space in the label.\n\n", line_num);
        break;

    case missingQuotation:
        printf("line: %d,missing quotation from a .string diractive statement\n\n", line_num);
        break;

    case undifinedLabel:
        printf("line: %d,usage of an undifined label\n\n");
        break;

    case labelIsStatement:
        printf("line: %d,label can't be a directive statement\n\n", line_num);
        break;

    case labelInstruction:
        printf("line: %d,label can't be an instruction\n\n", line_num);
        break;

    case labelIsExternal:
        printf("line: %d,label is already defined as being external\n\n", line_num);
        break;

    /*case labelIsInternal:
            printf("label is already defined as being internal");
            break;*/

    case notNumber:
        printf("line: %d,not a number\n\n", line_num);
        break;

    case notString:
        printf("line: %d,not a string\n\n", line_num);
        break;

    case tokenLength:
        printf("line: %d,token's length is higher than %d\n\n", line_num, max_row_len);
        break;

    case longRow:
        printf("line: %d,row too long(more than %d characters)\n\n", line_num, max_row_len);
        break;

    case invalidAdress:
        printf("line: %d,invalid adress\n\n", line_num);
        break;

    case manyLabelsSameRow:
        printf("line: %d, too many labels in the same row\n\n", line_num);
        break;

    case manyOpcodeSameLine:
        printf("line: %d, too many opcodes in the same line\n\n", line_num);
        break;

    case notValidRegister: 
        printf("line: %d, not a valid register\n\n", line_num);
        break;

    case longLabel:
        printf("line: %d, label too long (more then %d characters).\n\n", line_num, LABEL_LENGTH);
        break;

    case invalidLabel:
        printf("line: %d, invalid label\n\n");
        break;
    }
}

int valid_number(char *checkNum, int line)
{
    int i;

    if(checkNum == NULL)
    {
        printf("No variable of type number was obtained for the function\n");
        return FALSE;
    }

    else if((checkNum[0] == '#') || (checkNum[0] == '-') || (checkNum[0] == '+') || ((checkNum[0] >= '0' )&& (checkNum[0] <= '9')))
    {
        for(i=1; i <= strlen(checkNum); i++)
        {
            if((checkNum[i] < '0') || (checkNum[i] > '9'))
            {
                show_error(notNumber, line);
                return FALSE; /*error*/
            }  
        }
        return TRUE; /* is a valid number*/
    }
    else
    {
        return FALSE; /* checkNum[0] is not '#' , not a number and not '-' or '+' */
    }
}

int valid_register(char *reg, int line)
{
    int i;

    if (reg == NULL)
    {
        printf("No register variable was obtained for the function.\n");
        return FALSE;
    }
    else if ((reg[0] != 'r' ) || (reg[1] < '0')||(reg[1] > '7') || (strlen(reg) > 2))
    {
        show_error(notValidRegister, line);
        return FALSE;
    }
    return TRUE;
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
    int i, firstChar, firstAssci=0, lastAssci=177;
    
    if (string == NULL)
    {
        printf("the string variable is NULL.\n\n");
        return FALSE;
    }
    firstChar = count_spaces(string);
    if((string[firstChar] != ' " ') || (string[strlen(string)] != ' " '))// the first and last character in string need to be a : "
    {
        show_error(missingQuotation, line);
        return FALSE;// not valid string
    }
    else
    {
        for(i = firstChar ; i <= strlen(string) ; i++)
        {
            if((string[i] < firstAssci) && (string[i] > lastAssci))//if the characters not valid (ASSCI)
            {
                show_error(notString, line);
                return FALSE;//not valid string
            }
        }
        return TRUE;  //this is a valid string
    }
}

int defined_label(char *label, int line)
{
    return 0;
}

int valid_label(char *label, int line)
{
    int i, firstChar=0;

    if (label == NULL)
    {
        printf("the variable of the libel = NULL. \n\n");
        return FALSE;
    }


    firstChar = count_spaces(label); //Checks for white characters at the beginning of the string

    if ((strlen(label)-firstChar) > LABEL_LENGTH) //Checks the length of the label starting with the first letter
    {
        show_error(longLabel, line);
        return FALSE;
    }
    /* Checks if the label starts with a letter */
    else if((label[firstChar] >= 'A') && (label[firstChar] <= 'Z') || (label[firstChar] >= 'a') && (label[firstChar] <= 'z'))
    {
        for (i=firstChar+1 ; i <= strlen(label) ; i++) //A loop starts from the second character.
        {
            if(label[i] == ' ')//Check that there is no space in the middle of the label
            {
                show_error(whiteSpace, line);
                return FALSE;
            }
            else if (label[i] == ':' && (i != strlen(label)))//Check that there are no colon in the middle of the label
            {
                show_error(manyLabelsSameRow, line);
                return FALSE;
            }
            else if(((label[i] > '9') && (label[i] < 'A')) || ((label[i] > 'Z') && (label[i] < 'a' )) || (label[i] > 'z'))//Check that the characters after the first character are letters or numbers
            {
                show_error(invalidLabel, line);
                return FALSE;
            }
        }
        return TRUE; //valid label 

    }
    /* the first character is not a letter */
    else 
    {
        return FALSE;
    }
    
}

