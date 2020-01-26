DEBUG_FLAGS  := -g3


C_FLAGS          := $(DEBUG_FLAGS) -ansi -Wall
LD_FLAGS         :=

all : examine

examine : dummy_main.o examine.o
	gcc $(C_FLAGS) $(LD_FLAGS) -o examine dummy_main.o examine.o

dummy_main.o : dummy_main.c examine.h
	gcc $(C_FLAGS) -c -o dummy_main.o dummy_main.c
	
examine.o : examine.c
	gcc $(C_FLAGS) -c -o examine.o examine.c

.PHONY : clean

clean :
	rm -f *.o
	rm -f examine