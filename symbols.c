#include "MAIN.h"
#include "error_check.h"

int insert_into_symbol_table(int count_symbols, char *symbol_name, int num, char *type_of_symbol, struct symbols_table *symbols_list)
{
    struct symbols_table *new_label;
    new_label = (struct symbols_table *)malloc(sizeof(symbols_table));

    new_label->label = symbol_name;
    new_label->value = num;
    new_label->type_of_symbol = type_of_symbol;

    if (count_symbols == 0)
    {
        new_label->next = NULL;
        symbols_list = new_label;
    }
    else
    {
        new_label->next = symbols_list;
        symbols_list = new_label;
    }

    return 0;
}

insert_into_instruction_list(int count_i_lines, char *type_of_inst, char *info, char *pointer_to_row_in_symbol_table, struct instruction_line *instruction_line_list)
{
    struct instruction_line *new_inst_line;
    new_inst_line = (struct instruction_line *)malloc(sizeof(instruction_line));
    new_inst_line->label = pointer_to_row_in_symbol_table;
    new_inst_line->type_of_inst = type_of_inst;
    new_inst_line->info = info;

    if (count_i_lines == 0)
    {
        new_inst_line->next = NULL;
        instruction_line_list = new_inst_line;
    }
    else
    {
        new_inst_line->next = instruction_line_list;
        instruction_line_list = new_inst_line;
    }

    return 0;
}

insert_into_command_list(int count_c_lines, command *pointer_to_com, char *pointer_to_row_in_symbol_table, operand *operand_src, operand *operand_dest, command_line *command_line_list)
{
    int i = 0;
    struct command_line *new_command_line;
    new_command_line = (command_line *)malloc(sizeof(command_line));
    new_command_line->label = pointer_to_row_in_symbol_table;
    new_command_line->operand_src = operand_src;
    new_command_line->operand_dest = operand_dest;

    new_command_line->cmd = pointer_to_com;

    if (count_c_lines == 0)
    {
        new_command_line->next = NULL;
        command_line_list = new_command_line;
    }
    else
    {
        new_command_line->next = command_line_list;
        command_line_list = new_command_line;
    }
    return 0;
}

int erase_table()
{

    return 0;
}
