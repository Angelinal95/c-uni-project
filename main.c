#include "MAIN.h"

int main(int argc, char *argv[])
{
    int *wordMemoryArr;//for the second pass to print the output files
    int i;
    int numOfExtern = 0; //use in second read
    int numOfEntries = 0; //use in second read
    symbols_table *entryLabels = {0}; //use in second read
    symbols_table *dataArr; //use in the second read

    if (argc >= 1) // start of the program
    {

        for (i = 1; i < argc; i++)
        {
            
             main_pass(argv[i]); // first read

            if (!error)
            {
                
                second_pass(wordMemoryArr, entryLabels, dataArr, numOfEntries, IC, DC); // second read
            }

            /* If there are no errors */
	        if (!error) // If no errors, do the print to the files 
	        {
		        /* Create all the output files */
		        ObjectFile(argv[i], IC, DC, wordMemoryArr,dataArr);
		        ExternFile(argv[i], symbols_list , numOfExtern/*, linesArr, numOflines*/);
		        EntriesFile(argv[i], numOfEntries);
		        printf("success, output files for \"%s.as\" created.\n", argv[i]);

	        }
	    
        }
        return 1;
    }

    else
        return 0;
        
}
	

