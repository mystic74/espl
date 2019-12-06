.PHONY: all clean

all: task2b

task2b : task2b.o asm_cmpstr.o utoa_s.o
	gcc -m32 -o task2b task2b.o asm_cmpstr.o utoa_s.o -lc -I/lib/ld-linux.so.2

asm_cmpstr.o: asm_cmpstr.asm
	nasm -f elf32 -w+all -g -F dwarf -o asm_cmpstr.o asm_cmpstr.asm

utoa_s.o: utoa_s.asm
	nasm -f elf32 -w+all -o utoa_s.o utoa_s.asm

task2b.o: task2b.asm
	nasm -f elf32 -w+all -g -F dwarf -o task2b.o task2b.asm
	
clean:
	rm -rf *.o task2a