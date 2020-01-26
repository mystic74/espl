.PHONY: all clean

ASM_DEBUG := -g -F dwarf

all: task1b

task1b: dummy_main.o utoa_s.o
	gcc -m32 -o task1b dummy_main.o  utoa_s.o

dummy_main.o: dummy_main.c
	gcc -m32 -g -c -o dummy_main.o dummy_main.c

utoa_s.o: utoa_s.asm
	nasm -f elf32 -w+all $(ASM_DEBUG) -o utoa_s.o utoa_s.asm

clean:
	rm -rf *.o task1b