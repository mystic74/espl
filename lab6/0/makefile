DEBUG_FLAGS  := -g3


C_FLAGS          := $(DEBUG_FLAGS) -ansi -Wall
LD_FLAGS         :=

all : shell

shell : main.o LineParser.o
	gcc $(C_FLAGS) $(LD_FLAGS) -o shell main.o LineParser.o

main.o : main.c
	gcc $(C_FLAGS) -c -o main.o main.c

LineParser.o : LineParser.c
	gcc $(C_FLAGS) -c -o LineParser.o LineParser.c

.PHONY : clean

clean :
	rm -f *.o
	rm -f shell