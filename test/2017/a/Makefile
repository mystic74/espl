all: q2

q2: q2.o 
	gcc -m32 -o q2 q2.o -lc -I/lib/ld-linux.so.2
q2.o: q2_a.asm
	nasm -g -f elf32 -w+all -o q2.o q2_a.asm	
clean:
	rm -rf *.o q2
