DEBUG_FLAGS  := -g3 -m32


C_FLAGS          := $(DEBUG_FLAGS) -ansi -Wall
LD_FLAGS         :=

all : task2

task2 : task2.o examine.o
	gcc $(C_FLAGS) $(LD_FLAGS) -o task2 task2.o examine.o

task2.o : task2.c ../0/c/examine.h
	gcc $(C_FLAGS) -c -o task2.o task2.c 
	
examine.o : ../0/c/examine.c
	gcc $(C_FLAGS) -c -o examine.o ../0/c/examine.c

.PHONY : clean

clean :
	rm -f *.o
	rm -f task2