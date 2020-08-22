#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <mm_malloc.h>

#define INITIAL_ADDRESS 100

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

}symbols_table;

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

}command_line;

typedef struct 
{
    char *label; /*A pointer to the symbol_table*/
    char *type_of_inst;

    char *info;
     instruction_line *next;

}instruction_line;

typedef struct
{
    int address; // the IC in this
    int numOfWords; //A number of words that the instruction occupies in the machine code.
    char *opcode;
    char *adress_mode_src;
    char *operand_src;
    char *adress_mode_dest;
    char *operand_dest;
    char *funct;
    int A;
    int R;
    int E;
    int anotherValue; //if one of the registers == 0, and A == 1. so its a number in this instruction.
} full_instruction;


/* ****************************** structer to use in the Second Read ******************************/
typedef struct fullMemoryWord/* 24 bits */
{
    unsigned int E :1;
    unsigned int R :1;
    unsigned int A :1;
    union memWordType
    {
        struct instructionBits
        {
            unsigned int funct :5;
            unsigned int regDest :3;
            unsigned int modeDest :2;
            unsigned int regSrc :3;
            unsigned int modeSrc :2;
            unsigned int opcode :6;

        }instructionBits;

        struct dataBits
        {
            unsigned int number :21

        }dataBits;

    }wordType;   

} memWordcode;

/*-----------------------global variables-----------------------*/

int IC = 100;
int DC = 0;
int max_row_len = 80;
int line_num = 0; //the line number we're at
int error = 0;    //global variable to mark an errors
int g_numOfEntries = 0;
int g_numOfExterns =0;
symbols_table *labelList; // pointer to head of label list
symbols_table *entryLabelsList;
int line_num; //the line number we're at


/*------------------------functions----------------------------*/

/*------------------------Register List ------------------------*/

char registers[] = {
    {"r_0"}, {"r_1"}, {"r_2"}, {"r_3"}, {"r_4"}, {"r_5"}, {"r_6"}, {"r_7"}, {NULL}};

/*------------------------Commands List ------------------------*/
command command_list[] = {{"mov", 0, 0, 2}, {"cmp", 0, 1, 2}, {"add", 1, 2, 2}, {"sub", 2, 2, 2}, {"lea", 0, 4, 2}, {"clr", 1, 5, 1}, {"not", 2, 5, 1}, {"inc", 3, 5, 1}, {"dec", 4, 5, 1}, {"jmp", 1, 9, 1}, {"bne", 2, 9, 1}, {"jsr", 3, 9, 1}, {"red", 0, 12, 1}, {"prn", 0, 13, 1}, {"rts", 0, 14, 0}, {"stop", 0, 15, 0}, {NULL}};