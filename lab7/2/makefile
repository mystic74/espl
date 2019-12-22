DEBUG_FLAGS  := -g3


C_FLAGS 	 := $(DEBUG_FLAGS) -ansi -Wall -m32
LD_FLAGS	 := 

all : mypipe

mypipe : mypipe.o
	gcc $(C_FLAGS) $(LD_FLAGS) -o mypipe mypipe.o

mypipe.o : mypipe.c
	gcc $(C_FLAGS) -c -o mypipe.o mypipe.c

.PHONY : clean

clean : 
	rm -f *.o
	rm -f 1a
	rm -f 1b
	rm -f 1c
