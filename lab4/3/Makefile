all: task3

task3: task3.o 
	gcc -m32 -o task3 task3.o -lc -I/lib/ld-linux.so.2
task3.o: task3.asm
	nasm -g -f elf32 -w+all -o task3.o task3.asm	
clean:
	rm -rf *.o task3
