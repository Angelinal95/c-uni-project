#include "error_check.h"

void show_error(errorType typeName, int line_num)
{
    switch (typeName)
    {

    case function:
        printf("error in line: %d, there's no such function\n\n", line_num);
        break;

    case manyOperands:
        printf("error in line: %d, too many operands\n\n", line_num);
        break;

    case littleOperands:
        printf("error in line: %d, too little operands\n\n", line_num);
        break;

    case typeOperand:
        printf("error in line: %d, incorrect type of source operand\n\n", line_num);
        break;

    case typeDestination:
        printf("error in line: %d, incorrect type of destination operand\n\n", line_num);
        break;

    case destinationNotFound:
        printf("error in line: %d, destination operand doesn't exist\n\n", line_num);
        break;

    case sourceNotFound:
        printf("error in line: %d, source operand doesn't exist\n\n", line_num);
        break;

    case incorrectStatement:
        printf("error in line: %d, incorrect structure of the statement\n\n", line_num);
        break;

    case labelExists:
        printf("error in line: %d, label already exists\n\n", line_num);
        break;

    case savedWord:
        printf("error in line: %d, labale's name is the same as the name of a saved word\n\n", line_num);
        break;

    case whiteSpace:
        printf("error in line: %d, there's a white space in the label.\n\n", line_num);
        break;

    case missingQuotation:
        printf("error in line: %d, missing quotation from a .string diractive statement\n\n", line_num);
        break;

    case undifinedLabel:
        printf("error in line: %d, usage of an undifined label\n\n");
        break;

    case labelIsStatement:
        printf("error in line: %d, label can't be a directive statement\n\n", line_num);
        break;

    case labelInstruction:
        printf("error in line: %d, label can't be an instruction\n\n", line_num);
        break;

    case labelIsExternal:
        printf("error in line: %d, label is already defined as being external\n\n", line_num);
        break;

        /*case labelIsInternal:
            printf("error in line: %d, label is already defined as being internal.\n\n", line_num);
            break;*/

    case notNumber:
        printf("error in line: %d, not a number\n\n", line_num);
        break;

    case notString:
        printf("error in line: %d, not a string\n\n", line_num);
        break;

    case tokenLength:
        printf("error in line: %d, token's length is higher than %d\n\n", line_num, max_row_len);
        break;

    case longRow:
        printf("error in line: %d, row too long(more than %d characters)\n\n", line_num, max_row_len);
        break;

    case invalidAdress:
        printf("error in line: %d, invalid adress\n\n", line_num);
        break;

    case manyLabelsSameRow:
        printf("error in line: %d, too many labels in the same row\n\n", line_num);
        break;

    case manyOpcodeSameLine:
        printf("error in line: %d, too many opcodes in the same line\n\n", line_num);
        break;

    case notValidRegister:
        printf("error in line: %d, not a valid register\n\n", line_num);
        break;

    case longLabel:
        printf("error in line: %d, label too long (more then %d characters).\n\n", line_num, LABEL_LENGTH);
        break;

    case invalidLabel:
        printf("error in line: %d, invalid label\n\n");
        break;

    case invalidData:
        printf("error in line: %d, invalid data.\n\n");
        break;

    case invalidAddressingMode:
        printf("error in line: %d, invalid addressing mode.\n\n");
        break;

    case invalidFunc:
        printf("error in line: %d, invalid function.\n\n");
        break;
    }
}

int valid_number(char *checkNum, int line)
{
    int i;

    checkNum += count_spaces(checkNum); // skip the spaces in the begining of checkNum

    if (*checkNum == '#')
    {
        checkNum++;

        if ((*checkNum == '-') || (*checkNum == '+') || ((*checkNum >= '0') && (*checkNum <= '9')))

            for (i = 1; i <= strlen(checkNum); i++)
            {
                if ((checkNum[i] < '0') || (checkNum[i] > '9'))
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

    if (!isRegister(reg))
    {
        show_error(notValidRegister, line);
        return FALSE;
    }
    return TRUE;
}

int check_extern_label(char *strExtern, int line)
{
    int i, indexLabel = strspn(strExtern, ".extern"), word = 0;

    i = indexLabel;

    if (*(strExtern + i) == ' ')
    {
        i++;

        while (*(strExtern + i) != '\0')
        {
            if (*(strExtern + i) == ' ')
            {
                i++;
                continue;
            }
            else
            {
                while (*(strExtern + i) != ' ' && *(strExtern + i) != '\0')
                {
                    i++;
                }
                word++;
            }
        }
        if (word == 1)
        {
            if ((valid_label(strExtern + indexLabel, line)) /*&& (!(defined_label(strExtern+indexLabel, line)) )*/)
            {
                return TRUE;
            }
            else
                return FALSE;
        }

        else //(word == 0) || (word > 1)
        {
            show_error(incorrectStatement, line);
            return FALSE;
        }
    }
    else
    {
        return FALSE;
    }
}

int check_entry_label(char *entry, int line)
{
    int i, indexLabel = strspn(entry, ".entry"), word = 0;

    i = indexLabel;

    if (*(entry + i) == ' ')
    {
        i++;

        while (*(entry + i) != '\0')
        {
            if (*(entry + i) == ' ')
            {
                i++;
                continue;
            }
            else
            {
                while (*(entry + i) != ' ' && *(entry + i) != '\0')
                {
                    i++;
                }
                word++;
            }
        }
        if (word == 1)
        {
            if (valid_label(entry + indexLabel, line) && defined_label(entry + indexLabel, line))
            {
                return TRUE;
            }
            else
                return FALSE;
        }

        else //(word == 0) || (word > 1)
        {
            show_error(incorrectStatement, line);
            return FALSE;
        }
    }
    else
    {
        return FALSE;
    }
}

int name_function(char *nameFunc, int line)
{
    int found, i; // boolean found/not found.

    // deal with empty strings case.
    if (*nameFunc == '\0')
    {
        show_error(function, line);
        return FALSE;
    }

    for (i = 0; command_list[i].name != NULL; i++)
    {
        if (!strcmp(nameFunc, command_list[i].name))
        {
            return i; //return the index of the function in command_list
        }
    }

    show_error(function, line); // this is not a valid function
    return FALSE;
}

int valid_directive(char *directive, int line)
{

    if (strcmp(directive, ".data") == 0)
    {
        return TRUE;
    }
    else if (strcmp(directive, ".string") == 0)
    {
        return TRUE;
    }
    else if (strcmp(directive, ".entry") == 0)
    {
        return TRUE;
    }
    else if (strcmp(directive, ".extern") == 0)
    {
        return TRUE;
    }
    else
    {
        show_error(incorrectStatement, line);
        return FALSE;
    }
}

int valid_string(char *string, int line)
{
    int i, firstChar;
    char firstAssci = 32, lastAssci = 127;

    firstChar = count_spaces(string);

    if ((string[firstChar] != ' " ') || (string[strlen(string)] != ' " ')) // the first and last character in string need to be a : "
    {
        show_error(missingQuotation, line);
        return FALSE; // not valid string
    }
    else
    {
        for (i = firstChar; i <= strlen(string); i++)
        {
            if ((string[i] < firstAssci) && (string[i] > lastAssci)) //if the characters not valid (ASSCI)
            {
                show_error(notString, line);
                return FALSE; //not valid string
            }
        }
        return TRUE; //this is a valid string
    }
}

int valid_label(char *label, int line)
{
    int i, firstCharIndex = 0, lengthLabel = strlen(label);
    char tempLabel[LABEL_LENGTH];
    firstCharIndex = count_spaces(label); //Checks for white characters at the beginning of the string

    if (defined_label(label, line))
    {
        show_error(labelExists, line);
        return FALSE;
    }
    else if ((lengthLabel - firstCharIndex) > LABEL_LENGTH) //Checks the length of the label starting with the first letter
    {
        show_error(longLabel, line);
        return FALSE;
    }

    else if (*(label + lengthLabel - 1) != ':')
    {
        show_error(invalidLabel, line);
        return FALSE;
    }

    label += firstCharIndex;

    if (isRegister(label))
    {
        show_error(savedWord, line);
        return FALSE;
    }
    if (name_function(label, line) == FALSE)
    {
        /* Checks if the label starts with a letter */
        if ((*label >= 'A') && (*label <= 'Z') || (*label >= 'a') && (*label <= 'z'))
        {
            for (i = 1; i <= strlen(label); i++) //A loop starts from the second character.
            {
                if (label[i] == ' ') //Check that there is no space in the middle of the label
                {
                    show_error(whiteSpace, line);
                    return FALSE;
                }

                else if (((label[i] > '9') && (label[i] < 'A')) || ((label[i] > 'Z') && (label[i] < 'a')) || (label[i] > 'z')) //Check that the characters after the first character are letters or numbers
                {
                    show_error(invalidLabel, line);
                    return FALSE;
                }
            }
            return TRUE; //valid label
        }
    }
    /* the first character is not a letter */
    else
    {
        show_error(savedWord, line);
        return FALSE;
    }
}

int OnlySpacesAfterCode(char *str, int line)
{
    int i;

    for (i = 0; *(str + i) == ' '; i++)
        ;

    if (*(str + i) == '\0')
    {
        return TRUE;
    }
    else
    {
        show_error(incorrectStatement, line);
        return FALSE;
    }
}

int lebalInComment(char *label, int line)
{
    if (!defined_label(label, line))
    {
        show_error(undifinedLabel, line);
        return FALSE;
    }
    return TRUE;
}

/*checking if the label has been already defined*/
int defined_label(char *label, symbols_table *symbols_list)
{
    symbols_table *temp = &symbols_list;

    while (symbols_list != NULL)
    {
        if (strcmp(symbols_list[0].label, label) == 0)
        {

            return 1;
        }
        symbols_list = &symbols_list[1];
    }

    symbols_list = &temp;
    return 0;
}

/*for the second pass. In case there's a label that is defined extern but is actually defined in this file
and vide versa*/
int check_adress(char *adress, int line)
{
    return 0;
}