.PHONY: all clean

all: task2a

task2a : task2a.o 
	gcc -m32 -o task2a task2a.o  -lc -I/lib/ld-linux.so.2

task2a.o: task2a.asm
	nasm -f elf32 -w+all -o task2a.o task2a.asm
	
clean:
	rm -rf *.o task2a