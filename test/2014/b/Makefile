all: hello



q12: q12.o 
	gcc -m32 -o q12 q12.o -lc -I/lib/ld-linux.so.2
q12.o: q12.asm
	nasm -g -f elf32 -w+all -o q12.o q12.asm	

hello : q8.o
	gcc -m32 -o hello q8.o 

q8.o : q8.c
	gcc -m32 -c -o q8.o q8.c

# Either q7 or q8, same name.
#hello : q7.o
#	gcc -m32 -o hello q7.o 

q7.o : q7.c
	gcc -m32 -c -o q7.o q7.c

q9: q9.o 
	gcc -m32 -o q9 q9.o -lc -I/lib/ld-linux.so.2
q9.o: q9.asm
	nasm -g -f elf32 -w+all -o q9.o q9.asm	
clean:
	rm -rf *.o hello
