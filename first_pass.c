#include "MAIN.h"
#include "error_check.h"

struct command_line *command_line_list;
struct instruction_line *instruction_line_list;
struct symbols_table *symbols_list;
int count_c_lines = 0;
int count_i_lines = 0;
int count_symbols = 0;
struct symbols_table *pointer_to_row

    int
    main_pass(char *filename)
{
    FILE *fd;
    int line_count = 0;
    char temp[81];
    const char s[2] = " ";
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
        struct symbols_table *symbols_table = NULL;
        token = strtok(temp, s);

        //checking if the length of the line is more than 80 characters
        if (temp[81] != '/n')
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

    //checking if it's an empty line or a comment line
    int ignore_line(char *token)
    {

        return (skip_white_space(token) == NULL) || (strcmp(token, ";") == 0);
    }

    //analyzing what's in the current line
    int go_through_line(char *token, struct symbols_table *symbols_table)
    {
        char *temp_label = NULL;
        char *temp_com_or_inst;
        struct symbols_table *pointer_to_row = NULL;

        //checking if there's a label and taking care of it
        if (strchr(token, ':') != NULL)
        {
            if (legal_label(token) == 1)
            {
                temp_label = token;
                token = strtok(NULL, s);
            }
        }

        if (check_if_com_or_inst(token) == 1)
        {
            temp_com_or_inst = "data";

            if (strcmp(token, ".data") == 0)
            {
                token = strtok(NULL, s);
                if (valid_data(token))
                {
                    token = strtok(NULL, s);
                    insert_into_instruction_list(count_i_lines, ".data", pointer_to_row, token, instruction_line_list, search_row_in_symbol_table());
                    count_i_lines++;
                }
            }

            else if (strcmp(token, ".string") == 0)

            {
                token = strtok(NULL, s);

                if (valid_string(token))
                {
                    token = strtok(NULL, s);
                    insert_into_instruction_list(count_i_lines, ".string", pointer_to_row, token, instruction_line_list, search_row_in_symbol_table());
                    count_i_lines++;
                }
            }

            else if (strcmp(token, ".extern") == 0)
            {
                token = strtok(NULL, s)
            }
            /*if it's a .entry */
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
                char *operand_src;
                char *operand_dest;
                token = strtok(NULL, s);
                while (token != NULL)
                {
                    if (j == 0)
                    {

                        operand_src = token;
                    }
                    else if ((j == 1) && (strcmp(token, ',') != 0))
                    {
                        /*there's an error - func doesn't exist*/
                    }

                    else if (j == 2)
                    {
                        operand_dest = token;
                    }

                    j++;
                    token = strtok(NULL, s);
                }

                insert_into_command_list(count_c_lines, temp, pointer_to_row, symbols_list, operand_src, operand_dest, command_line_list);
                count_c_lines++;
            }
            else
            {
                /*there's an error - func doesn't exist*/
                return 0;
            }
        }

        if (temp_label != NULL)
        {
            if (strcmp(temp_com_or_ins, "code") == 0)
            {
                insert_into_symbols_table(count_symbols, temp_label, IC, temp_com_or_ins, symbols_list);
                count_symbols++;
            }
            else
            {
                insert_into_symbols_table(count_symbols, temp_label, DC, temp_com_or_ins, symbols_list);
                count_symbols++;
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
int search_row_in_symbol_table(struct symbols_table *symbols_list, char *temp_label, struct symbols_table *pointer_to_row)
{
    while (symbols_list->value != NULL)
    {
        if (strcmp(temp_label, symbols_list.label) == 0)
        {
            pointer_to_row = &symbols_list;
            return 1; /*if label was found*/
        }
        symbols_list = symbols_list->next;
    }

    return 0;
}

int is_Instant()
{

    return 0;
}
int is_Direct()
{

    return 0;
}
int is_Relative()
{

    return 0;
}
int is_register()
{

    return 0;
}

operand *build_operand()
{
    operand *new_operand;
    if (is_Instant() == 1)
    {
    }
    else if (is_Direct() == 1)
    {
    }
    else if (is_Relative() == 1)
    {
    }
    else if (is_register() == 1)
    {
    }
    else
    {

        /*error - complete it*/
    }

    return new_operand;
}

/*/* Adds the number to the g_dataArr and increases DC. Returns if it succeeded
bool addNumberToData(int num, int *IC, int *DC, int lineNum)
{
    /* Check if there is enough space in g_dataArr for the data 
    if (*DC + *IC < MAX_DATA_NUM)
    {
        g_dataArr[(*DC)++] = num;
    }
    else
    {
        return FALSE;
    }

    return TRUE;
}
*/
/* Adds the str to the g_dataArr and increases DC. Returns if it succeeded. 
bool addStringToData(char *str, int *IC, int *DC, int lineNum)
{
    do
    {
        if (!addNumberToData((int)*str, IC, DC, lineNum))
        {
            return FALSE;
        }
    } while (*str++);

    return TRUE;
}*/