#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <mm_malloc.h>

#define INITIAL_ADDRESS 100
#define ONE_BYTE_SIZE 8
#define ONE_WORD_SIZE 24

/*---------------------structers------------------------*/
typedef struct
{
    unsigned int Addressing_Mode;
    char *operand_value;

} operand;

typedef struct
{
    symbols_table *next;
    char *label;
    char *value;
    char *type_of_symbol;
    int address;
    int line;
    int L;

} symbols_table;

typedef struct
{
    char *name;
    unsigned int funct;
    unsigned int opcode;
    int numOfParams;

} command;

typedef struct
{
    char *label;        /*A pointer to the symbol_table*/
    const command *cmd; /* A pointer to the command in g_cmdArr */
    operand *operand_src;
    operand *operand_dest;
    command_line *next;
    int cLine;
    unsigned int A_R_E;

} command_line;

typedef struct
{
    char *label; /*A pointer to the symbol_table*/
    char *type_of_inst;
    int *info;
    instruction_line *next;

} instruction_line;

/* ****************************** structer to use in the Second Read ******************************/
typedef struct fullMemoryWord /* 24 bits */
{
    unsigned int A_R_E : 3;

    union memWordType
    {
        struct
        {
            unsigned int funct : 5;
            unsigned int regDest : 3;
            unsigned int modeDest : 2;
            unsigned int regSrc : 3;
            unsigned int modeSrc : 2;
            unsigned int opcode : 6;

        } instructionBits;

        unsigned int number : 21

    } wordVal;

} memWordCode;

int error = 0;

/*------------------------functions - first pass----------------------------*/

int main_pass(char *); //going through a text file
int ignore_line(char *);
int go_through_line(char *);      //analyzng eache character throught the line
int check_if_com_or_inst(char *); //checking if it's a command or an instruction
int skip_white_space(char *);
int search_row_in_symbol_table(char *, symbols_table *);   //searching for the adress of a specific label
int kind_of_addressing(operand *, char *, char *, char *); //checking the type od addressing
int add_symbol(char *, char *, int);                       //adding a new symbol to the symbols list

/*------------------------functions - second pass----------------------------*/

void completeLabelAddress(int ,int , symbols_table *, symbols_table *,symbols_table *, int *numOfEntries);
int countIllegalEntries(symbols_table *, int *);
symbols_table *searchLabel(char *);
int returnIntMemoryWord(memWordCode);
int returnModeOpType(operand);
int regNum(operand);
memWordCode lineMemWordCode(command_line);
void addWordToMemory(int *, int *, memWordCode);
void pushdataToMemory(symbols_table *, int *, int *, int);
void second_pass(int *, symbols_table *, symbols_table *, int *, int, int);

/*------------------------functions - symbols----------------------------*/

int insert_into_symbols_table(int, char *, int, char *, symbols_table *);                   //inserting a new node to the linked list of symbols
int insert_into_instruction_list(int, char *, char *, char *, instruction_line *);          //inserting a new node to the linked list of instructions
int insert_into_command_list(int, command *, char *, operand *, operand *, command_line *); //inserting a new node to the linked list of commands
void erase_symbol_table(symbols_table *);                                                   //erasing the whole symbols list
void erase_command_list(command_line *);                                                    //erasing the whole command list
void erase_instruction_list(instruction_line *);                                            //erasing the whole instruction list
void erase_instruction_line(instruction_line *);                                            //erasing the current node from the instruction line
void erase_command_line(command_line *);                                                    //erasing the current node from the command line

/*------------------------Register List ------------------------*/

char registers[] = {
    {"r_0"}, {"r_1"}, {"r_2"}, {"r_3"}, {"r_4"}, {"r_5"}, {"r_6"}, {"r_7"}, {NULL}};

/*------------------------Commands List ------------------------*/
command command_list[] = {{"mov", 0, 0, 2}, {"cmp", 0, 1, 2}, {"add", 1, 2, 2}, {"sub", 2, 2, 2}, {"lea", 0, 4, 2}, {"clr", 1, 5, 1}, {"not", 2, 5, 1}, {"inc", 3, 5, 1}, {"dec", 4, 5, 1}, {"jmp", 1, 9, 1}, {"bne", 2, 9, 1}, {"jsr", 3, 9, 1}, {"red", 0, 12, 1}, {"prn", 0, 13, 1}, {"rts", 0, 14, 0}, {"stop", 0, 15, 0}, {NULL}};