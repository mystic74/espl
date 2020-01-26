all: task1

task1: task1.o funcA.o
	gcc -m32 -o task1 task1.o funcA.o

task1.o: dummy_1.c
	gcc -m32 -g3 -c -o task1.o dummy_1.c
	
funcA.o: func_A.asm
	nasm -g -f elf32 -w+all -o funcA.o func_A.asm
clean:
	rm -rf *.o task0
