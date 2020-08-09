#include "MAIN.h"

enum error_type {function, manyOperands, littleOperands, typeOperand,
                     typeDestination, destinationNotFound, sourceNotFound,
                     incorrectStatement, labelExists, savedWord, whiteSpace,
                     missingQuotation, undifinedLabel, labelIsStatement, 
                     labelInstruction, labelIsExternal, labelIsInternal, 
                     notNumber, notString, tokenLength, longRow, invalidAdress, 
                     manyLabelsSameRow, manyOpcodeSameLine,notValidRegister};

void show_error(int, int);/*Prints an appropriate error message by error type*/
int valid_label(char *, int);/*Checks if the label is written legally*/
int defined_label(char *, int);/*When using a label in a command,
                                 we will check that such a label has been defined.*/
int valid_number(char *, int); /*Checks whether the number is integer (positive / negative)*/
int valid_string(char *, int); /*Checks if the string is valid*/
int valid_directive(char *, int);/**/
int valid_variable(char *, int);/*Checks whether the defined variables are valid*/
int valid_register(char *, int);/*Checking the validity of registers (r0-r7)*/
int name_function(char *, int);/*if legal action / function in assembly language*/
int check_address(char *, int);/**/
int check_entry_label(char *, int);/**/
int check_extern_label(char *, int);/**/