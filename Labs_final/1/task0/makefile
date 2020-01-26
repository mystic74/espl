CFLAGS := -m32 -ansi -Wall 
LDFLAGS :=

all : task0 echo

task0 : numbers.o main.o add.o
	gcc $(CFLAGS) $(LDFLAGS) -o task0 numbers.o main.o add.o 

numbers.o : numbers.c
	gcc $(CFLAGS) -c -o numbers.o numbers.c

main.o : main.c
	gcc $(CFLAGS) -c -o main.o main.c

add.o : add.s
	nasm -g -f elf -w+all -o add.o add.s

echo : echo.c
	gcc $(CFLAGS) -c -o echo.o echo.c
	gcc $(CFLAGS) $(LDFLAGS) -o echo echo.o

.clean_echo:
	rm -f echo

.clean_task0:
	rm -f task0
.PHONY : clean .clean_echo .clean_task0

clean: .clean_echo .clean_task0
	rm -f *.o
