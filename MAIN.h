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

    char *info;
    instruction_line *next;

} instruction_line;

typedef struct
{
    int address;    // the IC in this line of tne code
    int numOfWords; //A number of words that the instruction occupies in the machine code.
    int *opcode;
    char *adress_mode_src;
    char *operand_src;
    char *adress_mode_dest;
    char *operand_dest;
    int *funct;
    int A;
    int R;
    int E;
    int anotherValue; //if one of the registers == 0, and A == 1. so its a number in this instruction.
} full_instruction;

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

/*-----------------------global variables-----------------------*/

int max_row_len = 80;
int line_num = 0; //the line number we're at
int error = 0;    //global variable to mark an errors
int g_numOfEntries = 0;
int g_numOfExterns = 0;
int IC = INITIAL_ADDRESS;
int DC = 0;

symbols_table *entryLabelsList;
int line_num;                //the line number we're at
symbols_table *symbols_list; // pointer to head of label list
command_line *command_line_list;
instruction_line *instruction_line_list;

/*------------------------functions - first pass----------------------------*/
int main_pass(char *);            //function going through the text
int ignore_line(char *);          //checking if we should ignore the line
int go_through_line(char *);      //analyzing a single line
int check_if_com_or_inst(char *); //check if it's a command or an instruction
int skip_white_space(char *);
int search_row_in_symbol_table(char *, symbols_table *);   //looking for the adress of the label in the symbols list
int kind_of_addressing(operand *, char *, char *, char *); //checking the type if the addressing
int add_symbol(char *, char *, int);                       //adding a symbol to the symbols list

/*------------------------functions - symbols----------------------------*/
int insert_into_symbol_table(int, char *, int, char *);                     //adding a node into the linked list for the symbol table
int insert_into_instruction_list(int, char *, char *, char *);              //adding a node into the linked list for the instruction list
int insert_into_command_list(int, command *, char *, operand *, operand *); //adding a node into the linked list for the  command list
void erase_symbol_table();                                                  //erase the whole symbol table
void erase_command_list();                                                  //erase the whole command list
void erase_instruction_list();                                              //erase the whole instruction list
void erase_instruction_line();                                              //erase a node in the instruction list
void erase_command_line();                                                  //erase a node in the command list

/*------------------------functions - second pass----------------------------*/

void completeLabelAddress(int IC);
int countIllegalEntries();
int entryLabelAlreadyInList(char *entryLabelName);
symbols_table *searchLabel(char *labelName);
int ifOpIsLabel(operand *op, int lineNum);
int getNumFromMemoryWord(memWordCode memory);
int regNum(operand op);
memWordCode createCommandMemWord(command_line line);
memWordCode MemoryWord(command_line line);

/*------------------------Register List ------------------------*/

char registers[] = {
    {"r_0"}, {"r_1"}, {"r_2"}, {"r_3"}, {"r_4"}, {"r_5"}, {"r_6"}, {"r_7"}, {NULL}};

/*------------------------Commands List ------------------------*/
command command_list[] = {{"mov", 0, 0, 2}, {"cmp", 0, 1, 2}, {"add", 1, 2, 2}, {"sub", 2, 2, 2}, {"lea", 0, 4, 2}, {"clr", 1, 5, 1}, {"not", 2, 5, 1}, {"inc", 3, 5, 1}, {"dec", 4, 5, 1}, {"jmp", 1, 9, 1}, {"bne", 2, 9, 1}, {"jsr", 3, 9, 1}, {"red", 0, 12, 1}, {"prn", 0, 13, 1}, {"rts", 0, 14, 0}, {"stop", 0, 15, 0}, {NULL}};