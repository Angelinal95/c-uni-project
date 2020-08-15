#include "MAIN.h"
#include "error_check.h"

int insert_into_symbol_table(char *symbol_name, int num, char *type_of_symbol, struct symbols_table *symbols_list)
{
    struct symbols_table *new_label;
    new_label = (struct symbols_table *)malloc(sizeof(struct symbols_table));

    new_label->label = symbol_name;
    new_label->value = num;
    new_label->type_of_symbol = type_of_symbol;
    new_label->next = symbols_list;
    symbols_list = new_label;

    return 0;
}

insert_into_instruction_list(char *type_of_inst, char *info, char *pointer_to_row_in_symbol_table, struct instruction_line *instruction_line_list)
{
    struct instruction_line *new_inst_line;
    new_inst_line = (struct instruction_line *)malloc(sizeof(struct instruction_line));
    new_inst_line->label = pointer_to_row_in_symbol_table;
    new_inst_line->type_of_inst = type_of_inst;
    new_inst_line->info = info;
    new_inst_line->next = instruction_line_list;
    instruction_line_list = new_inst_line;

    return 0;
}

insert_into_command_list(command *pointer_to_com, char *pointer_to_row_in_symbol_table, char *operand_src, char *operand_dest, struct command_line *command_line_list)
{
    int i = 0;
    struct command_line *new_command_line;
    new_command_line = (struct command_line *)malloc(sizeof(struct command_line));
    new_command_line->label = pointer_to_row_in_symbol_table;
    new_command_line->operand_src = operand_src;
    new_command_line->operand_dest = operand_dest;

    new_command_line->cmd = pointer_to_com;

    new_command_line->next = command_line_list;
    command_line_list = new_command_line;

    return 0;
}

int erase_table()
{

    return 0;
}
