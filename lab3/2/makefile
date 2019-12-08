DEBUG_FLAGS  := -g3


C_FLAGS 	 := $(DEBUG_FLAGS) -ansi -Wall
LD_FLAGS	 := 

all : task2

task2 : 1a.o 2.o 
	gcc $(C_FLAGS) $(LD_FLAGS) -o task2 2.o 1a.o

2.o : 2.c
	gcc $(C_FLAGS) -c -o 2.o 2.c

1a.o : ../1/1a.c ../1/data_structs.h
	gcc $(C_FLAGS) -c -o 1a.o ../1/1a.c

.PHONY : clean

clean : 
	rm -f *.o task2
