#include "MAIN.h"
#include "error_check.h"

int insert_into_symbol_table(char *symbol_name, int num, char *type_of_symbol, symbols_table *symbols_list)
{
    symbols_table *new_label;
    new_label = (symbols_table *)malloc(sizeof(symbols_table));

    new_label->label = symbol_name;
    new_label->value = num;
    new_label->type_of_symbol = type_of_symbol;
    new_label->next = symbols_list;

    return 0;
}

   insert_into_instruction_list(char *type_of_inst, char *info, char *pointer_to_row_in_symbol_table){
   
        return 0;
   }

/*

   insert_into_command_list(char *type_of_inst, char *info, char *pointer_to_row_in_symbol_table){
   
        return 0;
   }
   
   */


int erase_table()
{

    return 0;
}
