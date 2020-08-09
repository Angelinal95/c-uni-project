#include "MAIN.h"

void show_error(int, int);
int legal_label(char *);
int defined_label(char *); //When using a label in a command, we will check that such a label has been defined.
int valid_number(char *);
int valid_string(char *);
int valid_directive(char *);
int valid_variable(char *);
int check_register(char *);
int name_function(char *);
int check_address(char *);
int check_entry_label(char *);
int check_extern_label(char *);
