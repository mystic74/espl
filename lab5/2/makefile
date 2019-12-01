.PHONY: all clean

all: task2a

task2a : 2a.o 
	gcc -m32 -o task2a 2a.o  -lc -I/lib/ld-linux.so.2

2a.o: 2a.asm
	nasm -f elf32 -w+all -o 2a.o 2a.asm
	
clean:
	rm -rf *.o task2a