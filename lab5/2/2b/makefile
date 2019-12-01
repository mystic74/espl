.PHONY: all clean

all: task2b

task2b : 2b.o my_strcmp.o utoa_s.o
	gcc -m32 -o task2b 2b.o my_strcmp.o utoa_s.o -lc -I/lib/ld-linux.so.2

my_strcmp.o: my_strcmp.asm
	nasm -f elf32 -w+all -g -F dwarf -o my_strcmp.o my_strcmp.asm
	
utoa_s.o: utoa_s.asm
	nasm -f elf32 -w+all -o utoa_s.o utoa_s.asm

2b.o: 2b.asm
	nasm -f elf32 -w+all -g -F dwarf -o 2b.o 2b.asm
	
clean:
	rm -rf *.o task2a