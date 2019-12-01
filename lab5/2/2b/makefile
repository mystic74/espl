.PHONY: all clean

all: task2b

task2b : 2b.o my_strcmp.o
	gcc -m32 -o task2b 2b.o my_strcmp.o -lc -I/lib/ld-linux.so.2

my_strcmp.o: my_strcmp.asm
	nasm -f elf32 -w+all -o my_strcmp.o my_strcmp.asm
	

2b.o: 2b.asm
	nasm -f elf32 -w+all -o 2b.o 2b.asm
	
clean:
	rm -rf *.o task2a