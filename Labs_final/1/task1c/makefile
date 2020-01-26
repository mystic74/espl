CFLAGS := -g -m32 -ansi -Wall 
LDFLAGS := 

task1c : my_atoi.o task1c.o atob.o upperlower.o
	gcc $(CFLAGS) $(LDFLAGS) -o char2ascii task1c.o my_atoi.o atob.o upperlower.o

upperlower.o : upperlower.c
	gcc $(CFLAGS) -c -o upperlower.o upperlower.c

atob.o : ../task1b/atob.c
	gcc $(CFLAGS) -c -o atob.o ../task1b/atob.c

my_atoi.o : ../task1a/my_atoi.c
	gcc $(CFLAGS) -c -o my_atoi.o ../task1a/my_atoi.c

task1c.o : task1c.c
	gcc $(CFLAGS) -c -o task1c.o task1c.c

.clean_task1c:
	rm -f char2ascii

.PHONY : clean .clean_task1c

clean: .clean_task1c
	rm -f *.o
