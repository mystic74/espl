.PHONY: all clean

all: task0

task0: task0.o my_close.o my_open.o
	gcc -m32 -o task0 task0.o my_open.o my_close.o

task0.o: 0.c
	gcc -m32 -c -o task0.o 0.c

my_close.o: my_close.asm
	nasm -f elf32 -w+all -o my_close.o my_close.asm

my_open.o: my_open.asm
	nasm -f elf32 -w+all -o my_open.o my_open.asm

clean:
	rm -rf *.o task0