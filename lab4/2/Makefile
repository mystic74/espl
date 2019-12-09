.PHONY: all clean

all: scmp_c scmp_asm

scmp_asm : scmp.o asm_cmpstr.o
	gcc -m32 -o scmp_asm scmp.o asm_cmpstr.o
scmp_c: scmp.o c_cmpstr.o
	gcc -m32 -o scmp_c scmp.o c_cmpstr.o
asm_cmpstr.o: asm_cmpstr.asm
	nasm -f elf32 -w+all -o asm_cmpstr.o asm_cmpstr.asm
	
c_cmpstr.o : c_cmpstr.c
	gcc -m32 -c -o c_cmpstr.o c_cmpstr.c
scmp.o: scmp.c
	gcc -m32 -c -o scmp.o scmp.c
	
clean:
	rm -rf *.o scmp_c scmp_asm