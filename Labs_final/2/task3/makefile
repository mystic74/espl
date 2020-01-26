C_FLAGS 	 := -g3 -ansi -Wall
LD_FLAGS	 := 

task3 : task3.o 2c.o 2b.o 2a.o
	gcc $(C_FLAGS) $(LD_FLAGS) -o task3 task3.o 2c.o 2b.o 2a.o

task3.o : 3.c
	gcc $(C_FLAGS) -c -o task3.o 3.c

2c.o : ../task2/2c.c
	gcc $(C_FLAGS) -c -o 2c.o ../task2/2c.c 

2b.o : ../task2/2b.c
	gcc $(C_FLAGS) -c -o 2b.o ../task2/2b.c 

2a.o : ../task2/2a.c
	gcc $(C_FLAGS) -c -o 2a.o ../task2/2a.c 
.PHONY : clean

clean : 
	rm *.o
	rm -f task3