all: q9 q12


q12: q12.o 
	gcc -m32 -o q12 q12.o -lc -I/lib/ld-linux.so.2
q12.o: q12.asm
	nasm -g -f elf32 -w+all -o q12.o q12.asm	

q11 : q11.o
	gcc -m32 -o q11 q11.o 

q11.o : q11.c
	gcc -m32 -c -o q11.o q11.c

q9: q9.o 
	gcc -m32 -o q9 q9.o -lc -I/lib/ld-linux.so.2
q9.o: q9.asm
	nasm -g -f elf32 -w+all -o q9.o q9.asm	
clean:
	rm -rf *.o q9 q11
