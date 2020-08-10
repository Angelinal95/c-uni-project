#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <mm_malloc.h>

/*---------------------structers------------------------*/


typedef struct
{
    symbols_table *next;
    char *label;
    char *value;
    char *type_of_symbol;

} symbols_table;


typedef struct {
	char *name;
     unsigned int funct;
	unsigned int opcode;
   int numOfParams;
} command;


typedef struct
{  
    char *label; /*A pointer to the symbol_table*/
	 const command *cmd; /* A pointer to the command in g_cmdArr */
    char *action;
    char *operand_src;
    char *operand_dest;

} command_line;

typedef struct
	
{     char *label; /*A pointer to the symbol_table*/
	char *type_of_inst; 
  
    char *info;

}instruction_line;



    
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







/*-----------------------global variables-----------------------*/

int IC = 100;
int DC = 0;
int max_row_len = 80;
int line_num; //the line number we're at
int error;    //global variable to mark an error

/*------------------------functions----------------------------*/



/*------------------------Register List ------------------------*/

char registers[] = {
    {"r_0"}, {"r_1"}, {"r_2"}, {"r_3"}, {"r_4"}, {"r_5"}, {"r_6"}, {"r_7"},{ NULL }};


/*------------------------Commands List ------------------------*/


command command_list[] = {{"mov", NULL, 0,2}, {"cmp",NULL,1,2}, {"add",1,2,2}, {"sub",2,2,2}, {"lea",NULL,4,2}, {"clr",1,5,1}, {"not",2,5,1}, {"inc",3,5,1}, {"dec",4,5,1}, {"jmp",1,9,1}, {"bne",2,9,1}, {"jsr"3,9,1}, {"red",NULL,12,1}, {"prn",NULL,13,1}, {"rts",NULL,14,0}, {"stop",NULL,15,0},{ NULL }};

