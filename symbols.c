#include "MAIN.h"
#include "error_check.h"

int insert_into_symbols_table(int count_symbols, char *symbol_name, char *values, char *type_of_symbol, symbols_table *symbols_list, int L, int ad)
{
    symbols_table *new_label;
    new_label = (symbols_table *)malloc(sizeof(symbols_table));

    new_label->label = symbol_name;
    new_label->value = values;
    new_label->address = ad;
    new_label->type_of_symbol = type_of_symbol;
    new_label->L = L;
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

int insert_into_instruction_list(int count_i_lines, char *type_of_inst, char *info, char *pointer_to_row_in_symbol_table, instruction_line *instruction_line_list)
{
    instruction_line *new_inst_line;
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

int insert_into_command_list(int count_c_lines, command *pointer_to_com, char *pointer_to_row_in_symbol_table, operand *operand_src, operand *operand_dest, command_line *command_line_list)
{
    int i = 0;
    command_line *new_command_line;
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

void erase_symbol_table(symbols_table *symbols_list)
{
    symbols_table *np, *u;

    while (symbols_list != NULL)
    {
        np = &symbols_list[0];
        u = np->next;
        free(np);
        symbols_list = u;
    }
}

void erase_command_list(command_line *command_line_list)
{
    command_line *np, *u;

    while (command_line_list != NULL)
    {
        np = &command_line_list[0];
        u = np->next;
        free(np);
        command_line_list = u;
    }
}

void erase_instruction_list(instruction_line *instruction_line_list)
{
    instruction_line *np, *u;

    while (instruction_line_list != NULL)
    {
        np = &instruction_line_list[0];
        u = np->next;
        free(np);
        instruction_line_list = u;
    }
}

void erase_instruction_line(instruction_line *instruction_line_list)
{
    instruction_line *np, *u;

    np = &instruction_line_list[0];
    u = np->next;
    free(np);
    instruction_line_list = u;
}

void erase_command_line(command_line *command_line_list)
{
    command_line *np, *u;

    np = &command_line_list[0];
    u = np->next;
    free(np);
    command_line_list = u;
}
