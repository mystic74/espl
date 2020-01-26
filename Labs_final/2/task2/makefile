DEBUG_FLAGS  := -g3


C_FLAGS 	 := $(DEBUG_FLAGS) -ansi -Wall -m32
LD_FLAGS	 := 

all : task2c task2b

task2c : dummy_main_2c.o 2c.o
	gcc $(C_FLAGS) $(LD_FLAGS) -o task2c dummy_main_2c.o 2c.o 2a.o

dummy_main_2c.o : dummy_main_2c.c
	gcc $(C_FLAGS) -c -o dummy_main_2c.o dummy_main_2c.c

2c.o : 2c.c 2a.o
	gcc $(C_FLAGS) -c -o 2c.o 2c.c

task2b : dummy_main_2b.o 2b.o 2a.o
	gcc $(C_FLAGS) $(LD_FLAGS) -o task2b dummy_main_2b.o 2b.o 2a.o

dummy_main_2b.o : dummy_main_2b.c
	gcc $(C_FLAGS) -c -o dummy_main_2b.o dummy_main_2b.c

2b.o : 2b.c
	gcc $(C_FLAGS) -c -o 2b.o 2b.c

2a.o : 2a.c
	gcc $(C_FLAGS) -c -o 2a.o 2a.c

.PHONY : clean

clean : 
	rm -f *.o
	rm -f task2b
	rm -f task2c
