#include "MAIN.h"

int main(int argc, char *argv[])
{
    int i;

    if (argc >= 1) // start of the program
    {

        for (i = 1; i < argc; i++)
        { 
             main_pass(argv[i]); // first read

        }
        return 1;
    }

    else
        return 0;
        
}
	

