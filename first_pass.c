#include "MAIN.h"
#include "error_check.h"

index_term registers[] = {
    {"r_0"}, {"r_1"}, {"r_2"}, {"r_3"}, {"r_4"}, {"r_5"}, {"r_6"}, {"r_7"}};

index_term func_list[] = {{"mov"}, {"cmp"}, {"add"}, {"sub"}, {"lea"}, {"clr"}, {"not"}, {"inc"}, {"dec"}, {"jmp"}, {"bne"}, {"jsr"}, {"red"}, {"prn"}, {"rts"}, {"stop"}};

index_term sentence_instruction[] = {{".data"}, {".string"}, {".entry"}, {".extern"}};

full_instruction *first_pass_full_instruction;

char *parts_of_sentence;

int main_pass(char *filename)
{
    FILE *fd;
    char *str;
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

    while (fgets(str, max_row_len + 1, fd) != NULL)

    {
        line_count++;
        error = 0;

        temp = strcpy(temp, str);
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

        return (skip_white_space(token)==NULL)||(*token==';'));
    }

    //analyzing what's in the current line
    int go_through_line(char *token)
    {

        //checking if there's a label and taking care of it
        if (strchr(str, ':') != NULL)
        {
            if ()
            {

                insert_into_label_table();
            }
        }

        //
        token = strtok(NULL, s)

            if (check_if_com_or_dir() == 1)
        {
            /* code */
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

    //determine if it's a command line or a direction line
    int check_if_com_or_dir()
    {
        if ()
        {

            return 1; //for a direction
        }
        return 0; //for a command
    };

    int is_label()
    {

        return 0;
    }

    int is_string_or_data()
    {

        return 0;
    }

    int is_entry_or_extern()
    {

        return 0;
    }
    int insert_into_label_table()
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
    }

    fclose(filename);

    second_pass();

    return 0;
}