#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<mm_malloc.h>

typedef struct
{
    char *term;
}index_term;


typedef struct {
    char *symbol;
    int value;
    char *type_of_symbol;

}hash_table;

#define hash_table first_pass_table[]={};

//global variables
int IC=100;
int DC=0;
int max_row_len=80;
int line_num; //the line number we're at
int error; //global variable to mark an error