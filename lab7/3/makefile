DEBUG_FLAGS  := -g3 #-DVERBOSE


C_FLAGS          := $(DEBUG_FLAGS) -ansi -Wall
LD_FLAGS         :=

all : shell

shell : main.o LineParser.o my_list.o 3_utils.o  cmdLine_utils.o pipes_utils.o
	gcc $(C_FLAGS) $(LD_FLAGS) -o shell main.o LineParser.o 3_utils.o pipes_utils.o cmdLine_utils.o

cmdLine_utils.o : cmdLine_utils.c
	gcc $(C_FLAGS) -c -o cmdLine_utils.o cmdLine_utils.c

pipes_utils.o : pipes_utils.c pipes_utils.h
	gcc $(C_FLAGS) -c -o pipes_utils.o pipes_utils.c

3_utils.o : env_var_utils.c
	gcc $(C_FLAGS) -c -o 3_utils.o env_var_utils.c

my_list.o : list_utils.c data_structs.h
	gcc $(C_FLAGS) -c -o my_list.o list_utils.c

main.o : main.c pipes_utils.h
	gcc $(C_FLAGS) -c -o main.o main.c

LineParser.o : LineParser.c
	gcc $(C_FLAGS) -c -o LineParser.o LineParser.c

.PHONY : clean

clean :
	rm -f *.o
	rm -f 3/*.o
	rm -f shell
