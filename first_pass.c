#include "MAIN.h"
#include "error_check.h"

index_term registers[] = {
    {"r_0"}, {"r_1"}, {"r_2"}, {"r_3"}, {"r_4"}, {"r_5"}, {"r_6"}, {"r_7"}};

index_term command_list[] = {{"mov"}, {"cmp"}, {"add"}, {"sub"}, {"lea"}, {"clr"}, {"not"}, {"inc"}, {"dec"}, {"jmp"}, {"bne"}, {"jsr"}, {"red"}, {"prn"}, {"rts"}, {"stop"}};

symbols_table *symbols_table;

int main_pass(char *filename)
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
                go_through_line(token);
            }
        }
    }

    //checking if it's an empty line or a comment line
    int ignore_line(char *token)
    {

        return (skip_white_space(token) == NULL) || (strcmp(token, ";"));
    }

    //analyzing what's in the current line
    int go_through_line(char *token)
    {
        char *temp_label = NULL;
        char *temp_com_or_inst;

        //checking if there's a label and taking care of it
        if (strchr(str, ':') != NULL)
        {
            if (is_valid_label(token) == 1)
            {
                temp_label = token;
            }
        }

        token = strtok(NULL, s)

            if (check_if_com_or_inst(token) == 1)
        {
            temp_com_or_inst = "data";

            if (strcmp(token, ".data"))
            {
            }

            else if (strcmp(token, ".string"))
            {
            }

            else if (.extern)
            {
            }

            else
            {

                return 0;
            }
        }

        else
        {
            temp_com_or_inst = "code";
            if (is_valid_command() == 1)
            {
            }
            else
            {
                return 0;
            }
        }

        if (temp_label != NULL)
        {
            insert_into_symbols_table(temp_label, temp_com_or_ins);
        }

        token = strtok(NULL, s)

            if (token != NULL)
        {
            token = strtok(NULL, s)

                if (token != NULL)
            {
            }
        }
    }

    fclose(filename);

    second_pass();

    return 0;
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

//inserting a label into the symbols table
int insert_into_symbols_table(char *label, char *type_of_symbol)
{

    return 0;
}

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

/*error check*/
int is_valid_label(char *token)
{
    return 0;
}

int is_valid_command(char *token)
{
    return 0;
}

int is_valid_num_of_operands()
{

    return 1;
}