CFLAGS := -g -m32 -ansi -Wall 
LDFLAGS := 

task2 : my_atoi.o task2.o atob.o upperlower.o
	gcc $(CFLAGS) $(LDFLAGS) -o char2ascii task2.o my_atoi.o atob.o upperlower.o

upperlower.o : ../task1c/upperlower.c
	gcc $(CFLAGS) -c -o upperlower.o ../task1c/upperlower.c

atob.o : ../task1b/atob.c
	gcc $(CFLAGS) -c -o atob.o ../task1b/atob.c

my_atoi.o : ../task1a/my_atoi.c
	gcc $(CFLAGS) -c -o my_atoi.o ../task1a/my_atoi.c

task2.o : task2.c
	gcc $(CFLAGS) -c -o task2.o task2.c

.clean_task2:
	rm -f char2ascii

.PHONY : clean .clean_task2

clean: .clean_task2
	rm -f *.o
