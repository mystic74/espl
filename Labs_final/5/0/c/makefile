.PHONY: all clean

all: scmp

scmp: scmp.o my_strcmp.o
	gcc -m32 -o scmp scmp.o my_strcmp.o

scmp.o: scmp.c
	gcc -m32 -c -o scmp.o scmp.c

my_strcmp.o: my_strcmp.asm
	nasm -f elf32 -w+all -o my_strcmp.o my_strcmp.asm
	
clean:
	rm -rf *.o scmp