%.o: %.asm
	nasm -g -O1 -g -F dwarf -f elf -o $@ $<

%.o: %.c
	gcc -m32 -g3 -nostdlib -fno-stack-protector -c -o $@ $<

all: lwca

lwca: lwc.o start.o
	ld  -melf_i386 -o $@ $^

clean:
	rm -f *.o lwca
