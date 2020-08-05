#include "MAIN.h"
#include "error_check.h"

index_term registers[]={
    {"r_0"},{"r_1"},{"r_2"},{"r_3"},{"r_4"},{"r_5"},{"r_6"},{"r_7"}
};

index_term action_instruction[]={{"mov"},{"cmp"},{"add"},{"sub"},{"lea"},{"clr"},{"not"},
{"inc"},{"dec"},{"jmp"},{"bne"},{"jsr"},{"red"},{"prn"},{"rts"},{"stop"}};

index_term sentence_instruction[]={{".data"},{".string"},{".entry"},{".extern"}};

int main_pass(char* filename){
    FILE *fd;
    char *str;
    fd=fopen(filename, "r");

    if (fd == NULL){
        printf("Could not open file %s",filename);
        return 1;
    }

    while (!feof(fd))
    {
        
    }
    

    while (fgets(str, max_row_len, fd) != NULL){
        printf("%s", str);
    }

    
    fclose(filename);
    return 0;

}