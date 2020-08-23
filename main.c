#include "MAIN.h"

int main(int argc, char *argv[])
{
    int i;
    FILE * file;

    if (argc >= 1)
    {

        for (i = 1; i < argc; i++)
        {
            if (!(file = fopen(argv[i], "r"))) 
            {
		        printf("Cant open the file: %s.as \n", argv[i]);
                continue;
            }
            /* First Read */
             main_pass(argv[i]);

            if (!error)
            {
                /* Second Read */
                 secondPass(argv[i]);
            }

            /* If there are no errors */
	        if (!error)
	        {
		        /* Create all the output files */
		        ObjectFile(argv[i], IC, DC/*, memoryArr*/);
		        ExternFile(argv[i]/*, linesArr, numOflines*/);
		        EntriesFile(argv[i]);
		        printf("success, output files for \"%s.as\" created.\n", argv[i]);

	        }
	    
        }
        return 1;
    }

    else
        return 0;
        
}
	

