DEBUG_FLAGS  := -m32 -g3


C_FLAGS          := $(DEBUG_FLAGS) -ansi -Wall
LD_FLAGS         :=

all : task1

task1 : task1.o examine.o
	gcc $(C_FLAGS) $(LD_FLAGS) -o task1 task1.o examine.o

task1.o : task1.c ../0/c/examine.h
	gcc $(C_FLAGS) -c -o task1.o task1.c 
	
examine.o : ../0/c/examine.c
	gcc $(C_FLAGS) -c -o examine.o ../0/c/examine.c

.PHONY : clean

clean :
	rm -f *.o
	rm -f task1