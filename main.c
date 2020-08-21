#include "MAIN.h"

int main(int argc, char *argv[])
{
    int i, numOfErrors = 0;

    if (argc >= 1)
    {
        for (i = 1; i < argc; i++)
        {
            /* First Read */
            numOfErrors += first_pass(argv[i]);
            /* Second Read */
            numOfErrors += secondPass(argv[i]);

            /* If there are no errors */
	        if (numOfErrors == 0)
	        {
		        /* Create all the output files */
		        createObjectFile(argv[i], IC, DC/*, memoryArr*/);
		        createExternFile(argv[i]/*, linesArr, numOflines*/);
		        createEntriesFile(argv[i]);
		        printf("success, output files for the file \"%s.as\" were created.\n", argv[i]);
	        }
	    
        }
        return 1;
    }

    else
        return 0;
        
}
	

