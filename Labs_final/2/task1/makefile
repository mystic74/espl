DEBUG_FLAGS  := -g3


C_FLAGS 	 := $(DEBUG_FLAGS) -ansi -Wall -m32
LD_FLAGS	 := 

task1c : task1c.o
	gcc $(C_FLAGS) $(LD_FLAGS) -o task1c task1c.o 

task1c.o : 1c.c
	gcc $(C_FLAGS) -c -o task1c.o 1c.c

task1 : task1.o
	gcc $(C_FLAGS) $(LD_FLAGS) -o task1 task1.o 

task1.o : addresses.c
	gcc $(C_FLAGS) -c -o task1.o addresses.c

.PHONY : clean

clean : 
	rm -f *.o
	rm -f task1
	rm -f task1c
