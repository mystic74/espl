.PHONY: all clean

all: scmp

scmp: scmp.o
	gcc -m32 -o scmp scmp.o

scmp.o: scmp.c
	gcc -m32 -c -o scmp.o scmp.c
	
clean:
	rm -rf *.o scmp