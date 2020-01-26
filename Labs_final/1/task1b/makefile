CFLAGS := -g -m32 -ansi -Wall 
LDFLAGS := 

task1b : my_atoi.o task1b.o atob.o
	gcc $(CFLAGS) $(LDFLAGS) -o char2ascii task1b.o my_atoi.o atob.o

atob.o : atob.c
	gcc $(CFLAGS) -c -o atob.o atob.c

my_atoi.o : ../task1a/my_atoi.c
	gcc $(CFLAGS) -c -o my_atoi.o ../task1a/my_atoi.c

task1b.o : task1b.c
	gcc $(CFLAGS) -c -o task1b.o task1b.c

.clean_task1b:
	rm -f char2ascii

.PHONY : clean .clean_task1b

clean: .clean_task1b
	rm -f *.o
