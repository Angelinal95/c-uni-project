#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <mm_malloc.h>

/*---------------------structers------------------------*/
typedef struct
{
    char *term;
} index_term;

typedef struct
{
    symbols_table *next;
    char *label;
    char *value;
    char *type_of_symbol;

} symbols_table;

typedef struct
{
    char *opcode;
    char *adress_mode_src;
    char *operand_src;
    char *adress_mode_dest;
    char *operand_dest;
    char *funct;
    int A;
    int R;
    int E;
} full_instruction;

typedef struct
{
    char *label;
    char *action;
    char *operand_src;
    char *operand_dest;

} break_sentence;

#define hash_table first_pass_table[] = {};

/*---------------------global variables-------------------*/

int IC = 100;
int DC = 0;
int max_row_len = 80;
int line_num; //the line number we're at
int error;    //global variable to mark an error

/*------------------------functions------------------------*/