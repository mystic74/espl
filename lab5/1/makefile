.PHONY: all clean

all: task1b

task1b: task1b.o utoa_s.o
	gcc -m32 -o task1b task1b.o  utoa_s.o

task1b.o: task1b.c
	gcc -m32 -g -c -o task1b.o task1b.c

utoa_s.o: utoa_s.asm
	nasm -f elf32 -w+all -o utoa_s.o utoa_s.asm

clean:
	rm -rf *.o task1b