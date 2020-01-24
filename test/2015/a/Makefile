.PHONY: all clean

all: q2 

q2 : q2.o
	gcc -m32 -o q2 q2.o

q2.o : q2.c
	gcc -m32 -c -o q2.o q2.c

#q1: q1.o func.o
#	gcc -m32 -o q1 q1.o func.o

#func.o: 1func.asm
#	nasm -f elf32 -w+all -o func.o 1func.asm

#q1.o : q1.c
#	gcc -m32 -c -o q1.o q1.c
	
clean:
	rm -rf *.o q1 q2