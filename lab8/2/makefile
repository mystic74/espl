DEBUG_FLAGS  := -g3


C_FLAGS          := $(DEBUG_FLAGS) -ansi -Wall
LD_FLAGS         :=

all : task2

task2 : 2.o examine.o
	gcc $(C_FLAGS) $(LD_FLAGS) -o task2 2.o examine.o

2.o : 2.c ../0/c/examine.h
	gcc $(C_FLAGS) -c -o 2.o 2.c 
	
examine.o : ../0/c/examine.c
	gcc $(C_FLAGS) -c -o examine.o ../0/c/examine.c

.PHONY : clean

clean :
	rm -f *.o
	rm -f task2