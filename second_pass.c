#include "MAIN.h"
#include "error_check.h"

typedef struct{
    char *func_name;
    int func_num;
    int op_code;
}func_table;

func_table func_table_1[]={
    {"mov",NULL, 0},{"cmp",NULL,1},{"add",1,2},{"sub",2,2},{"lea",NULL,4},
    {"clr",1,5},{"not",2,5},{"inc",3,5},{"dec",4,5},{"jmp",1,9},
    {"bne",2,9},{"jsr",3,9},{"red",NULL,12},{"prn",NULL,"13"},{"rts",NULL,14},
    {"stop",NULL,15}

}