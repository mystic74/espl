CFLAGS := -g -m32 -ansi -Wall 
LDFLAGS := 


task1a : my_atoi.o task1a.o 
	gcc $(CFLAGS) $(LDFLAGS) -o char2ascii task1a.o my_atoi.o

my_atoi.o : my_atoi.c
	gcc $(CFLAGS) -c -o my_atoi.o my_atoi.c

task1a.o : task1a.c
	gcc $(CFLAGS) -c -o task1a.o task1a.c

.clean_task1a:
	rm -f char2ascii

.PHONY : clean .clean_task1a

clean: .clean_task1a
	rm -f *.o
