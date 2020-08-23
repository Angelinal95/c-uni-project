#include "MAIN.h"
#include "error_check.h"
#include "auxiliary_functions.h"

int count_c_lines = 0;
int count_i_lines = 0;
int count_symbols = 0;
symbols_table *pointer_to_row = NULL;
char s[2] = " ";

int main_pass(char *filename)
{
    FILE *fd;
    int line_count = 0;
    char temp[81];
    char temp_1[81];
    char *token;

    fd = fopen(filename, "r");

    if (fd == NULL)
    {
        printf("Could not open file %s", filename);
        return 1;
    }

    while (fgets(temp, max_row_len + 1, fd) != NULL)

    {
        line_count++;
        error = 0;
        symbols_table *symbols_table = NULL;
        token = strtok(temp, s);

        //checking if the length of the line is more than 80 characters

        if ((temp[81] != '/n') && (fgets(temp_1, max_row_len + 1, fd) != NULL))
        {
            show_error(20, line_count);
        }
        else
        {
            if (ignore_line(token) == 0)
            {
                go_through_line(token, symbols_table);
            }
        }

        fclose(filename);

        second_pass();

        return 0;
    }

    int ICF = IC;
    int DCF = DC;

    second_pass(symbols_list, instruction_line_list, command_line_list, ICF, DCF);
}
//checking if it's an empty line or a comment line
int ignore_line(char *token)
{

    return ((skip_white_space(token) == NULL) || (strcmp(token, ";") == 0));
}

//analyzing what's in the current line
int go_through_line(char *token, struct symbols_table *symbols_table)
{
    char *temp_label = NULL;
    int flag_for_extern = 0;
    char *temp_com_or_inst;

    //checking if there's a label and taking care of it
    if (strchr(token, ':') != NULL)
    {
        if (valid_label(token, line_num) == TRUE)
        {
            temp_label = token;
            token = strtok(NULL, s);
        }
        else
        {
            return 0;
        }
    }

    if (check_if_com_or_inst(token) == 1)
    {
        temp_com_or_inst = "data";

        if (strcmp(token, ".data") == 0)
        {
            token = strtok(NULL, s);
            int *temp_arr_for_data = NULL;
            while (token != NULL)
            {
                token = strtok(NULL, s);
                if (valid_number(token) == TRUE)
                {
                    count_i_lines++;
                    DC++;
                    temp_arr_for_data = (int *)calloc(token, sizeof(int));
                }
                else
                {

                    return 0;
                }
            }
            insert_into_instruction_list(count_i_lines, ".data", pointer_to_row, temp_arr_for_data, instruction_line_list, search_row_in_symbol_table());
        }

        else if (strcmp(token, ".string") == 0)
        {
            token = strtok(NULL, s);

            if (valid_string(token) == TRUE)
            {
                token = strtok(NULL, s);

                insert_into_instruction_list(count_i_lines, ".string", pointer_to_row, token, instruction_line_list, search_row_in_symbol_table());
                count_i_lines++;

                DC = DC + strlen(token) + 1;
            }
            else
            {
                return 0;
            }
        }

        else if (strcmp(token, ".extern") == 0)
        {
            token = strtok(NULL, s);
            if((check_extern_label(token, line_num)==TRUE){
                insert_into_instruction_list(count_i_lines, ".extern", pointer_to_row, token, instruction_line_list, search_row_in_symbol_table());
                token = strtok(NULL, s);
                flag_for_extern = 1;

            }
            else{
                return 0;
            }
        }
        /*if it's an .entry */
        else
        {
            return 0;
        }
    }

    else
    {
        temp_com_or_inst = "code";
        command *temp;
        int i = 0;
        while (command_list[i].name != NULL)
        {
            if (strcmp(token, command_list[i].name) == 0)
            {
                temp = &command_list[i];

                break;
            }
            i++;
        }

        if (i < 16)
        {
            int j = 0;
            int temp_for_address = 0;
            ++IC;
            operand *operand_src = NULL;
            operand *operand_dest = NULL;
            token = strtok(NULL, s);
            while (token != NULL)
            {
                if (j == 0)
                {
                    temp_for_address = kind_of_addressing(operand_src, token, temp_label, temp_com_or_inst);
                    if (temp_for_address == 4)
                    {
                        show_error(invalidAddressingMode, line_num);
                        return 0;
                    }
                    if ((operand_src->Addressing_Mode) != 3)
                    {
                        IC = IC + 2;
                    }
                }
                else if ((j == 1) && (strcmp(token, ',') != 0))
                {
                    show_error(function, line_num);
                    return 0;
                }

                else if (j == 2)
                {

                    temp_for_address = kind_of_addressing(operand_dest, token, temp_label, temp_com_or_inst);
                    if ((temp_for_address) == 4)
                    {
                        show_error(invalidAddressingMode, line_num);
                        return 0;
                    }
                    if (((operand_dest->Addressing_Mode) == 0) || ((operand_dest->Addressing_Mode) == 2))
                    {
                        IC = IC + 2;
                    }
                    if ((operand_dest->Addressing_Mode) == 1)
                    {
                        IC = IC + 1;
                    }
                }

                j++;
                token = strtok(NULL, s);
            }

            if ((j == 2) && ((i > 13) || (i < 5)))
            {
                show_error(littleOperands, line_num);

                free(operand_src);

                return 0;
            }
            else if (j == 1)
            {
                if (i < 5)
                {
                    show_error(manyOperands, line_num);
                    free(operand_src);
                    free(operand_dest);
                }
                else if (i > 14)
                {
                    show_error(littleOperands, line_num);
                    free(operand_src);
                }

                return 0;
            }

            else if ((j == 0) && (i < 14))
            {
                show_error(manyOperands, line_num);
                free(operand_src);
                if (i < 5)
                {

                    free(operand_dest);
                }

                return 0;
            }

            insert_into_command_list(count_c_lines, temp, pointer_to_row, symbols_list, operand_src, operand_dest, command_line_list);
            count_c_lines++;
        }
        else
        {
            show_error(invalidFunc, line_num);
            return 0;
        }
    }

    if (temp_label != NULL)
    {
        if (defined_label(temp_label, symbols_list) != 1)
        {

            if (strcmp(temp_com_or_ins, "code") == 0)
            {
                insert_into_symbols_table(count_symbols, temp_label, IC, temp_com_or_ins, symbols_list);
                count_symbols++;
            }
            else
            {
                if (flag_for_extern == 1)
                {
                    insert_into_symbols_table(count_symbols, temp_label, 0, "external", symbols_list);
                }

                else
                {
                    insert_into_symbols_table(count_symbols, temp_label, DC, temp_com_or_ins, symbols_list);
                }
                count_symbols++;
            }
        }
        else
        { /*function to delete line in instruction or command*/
            if (strcmp(temp_com_or_ins, "data") == 0)
            {
                erase_instruction_line();
            }
            else
            {
                erase_command_line();
            }

            show_error(labelExists, line_num);
            return 0;
        }
    }
}
}

//determine if it's a command line or a instruction line
int check_if_com_or_inst(char *token)
{

    //if it's an instruction
    if (strchr(str, '.') != NULL)
    {
        return 1;
    }
    //if it's a command
    return 0;
};

int skip_white_space(char *token)
{
    char temp = *token;
    while ((isspace() != 0) && (token != NULL))
    {
        token = ++token;
        temp = *token;
    }
    return 0;
}

/*get the adress of the label*/
int search_row_in_symbol_table(symbols_table *symbols_list, char *temp_label, symbols_table *pointer_to_row)
{
    while (symbols_list->value != NULL)
    {
        if (strcmp(temp_label, symbols_list->label) == 0)
        {
            pointer_to_row = &symbols_list;
            return 1; /*if label was found*/
        }
        symbols_list = symbols_list->next;
    }

    return 0;
}

int kind_of_addressing(operand *op, char *token, char *temp_label, char *temp_com_or_inst)
{

    //checking if it's Instant addressing

    if (token[0] == '#')
    {
        token = &token[1];
        if (valid_number(token, line_num) == TRUE)
        {
            op->operand_value = token;
            op->Addressing_Mode = 0;
        }
        return 4;
    }

    if (temp_label != NULL)
    { //checking if it's Direct addressing
        if (strcmp(temp_com_or_inst, "data") == 0)
        {
            op->operand_value = token;
            op->Addressing_Mode = 1;
        }
        //checking if it's Relative addressing

        else if (token[0] == '&')
        {
            token = &token[1];
            op->operand_value = token;
            op->Addressing_Mode = 2;
        }
        return 4;
    }

    //checking if it's Direct register addressing
    if (valid_register(token, line_num))
    {
        op->operand_value = token;
        op->Addressing_Mode = 3;
    }

    return 4;
}
