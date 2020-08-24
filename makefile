fullProject: main.o first_pass.o symbols.o second_pass.o file_function.o error_check.o auxiliary_function.o
			 gcc -g -ansi -Wall -pedantic main.o first_pass.o symbols.o second_pass.o file_function.o error_check.o auxiliary_function.o -o fullProject

main.o: main.c MAIN.h
		gcc -c -ansi -Wall -pedantic main.c -o main.o

first_pass.o: first_pass.c MAIN.h
			  gcc -c -ansi -Wall -pedantic first_pass.c -o first_pass.o

symbols.o: symbols.c MAIN.h error_check.h
			gcc -c -ansi -Wall -pedantic symbols.c -o symbols.o

second_pass.o: second_pass.c error_check.h MAIN.h
			gcc -c -ansi -Wall -pedantic second_pass.c -o second_pass.o


file_function.o: file_functions.c file_functions.h
			gcc -c -ansi -Wall -pedantic file_function.c -o file_function.o


error_check.o: error_check.c error_check.h
			gcc -c -ansi -Wall -pedantic error_check.c -o error_check.o


auxiliary_function.o: auxiliary_function.c auxiliary_function.h MAIN.h
			gcc -c -ansi -Wall -pedantic auxiliary_function.c -o auxiliary_function.o

