C_FLAGS 	 := -g3 -ansi -Wall
LD_FLAGS	 := 

task2 : task3.o 2c.o 2b.o 2a.o
	gcc $(C_FLAGS) $(LD_FLAGS) -o task3 task3.o 2c.o 2b.o 2a.o

task2.o : 3.c
	gcc $(C_FLAGS) -c -o task3.o 3.c

2c.o : ../2c/2c.c
	gcc $(C_FLAGS) -c -o 2c.o ../2c/2c.c 

2b.o : ../2b/2b.c
	gcc $(C_FLAGS) -c -o 2b.o ../2b/2b.c 

2a.o : ../2a/2a.c
	gcc $(C_FLAGS) -c -o 2a.o ../2a/2a.c 
.PHONY : clean

clean : 
	rm *.o
	rm -f task3
