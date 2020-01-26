DEBUG_FLAGS  := -g3


C_FLAGS 	 := $(DEBUG_FLAGS) -ansi -Wall -m32
LD_FLAGS	 := 

all : 1a 1b 1c bcmp

bcmp : 2.o
	gcc $(C_FLAGS) $(LD_FLAGS) -o bcmp 2.o 1a.o

2.o : 2.c data_structs.h
	gcc $(C_FLAGS) -c -o 2.o 2.c

1c : 1c.o 1a.o
	gcc $(C_FLAGS) $(LD_FLAGS) -o 1c 1c.o 1a.o

1c.o : 1c.c
	gcc $(C_FLAGS) -c -o 1c.o 1c.c

1b : 1b.o 1a.o
	gcc $(C_FLAGS) $(LD_FLAGS) -o 1b 1b.o 1a.o

1b.o : 1b.c data_structs.h
	gcc $(C_FLAGS) -c -o 1b.o 1b.c

1a: 1a_dummy.o 1a.o
	gcc $(C_FLAGS) $(LD_FLAGS) -o 1a 1a_dummy.o 1a.o

1a_dummy.o : 1a_dummy_main.c data_structs.h
	gcc $(C_FLAGS) -c -o 1a_dummy.o 1a_dummy_main.c

1a.o : 1a.c data_structs.h
	gcc $(C_FLAGS) -c -o 1a.o 1a.c

.PHONY : clean

clean : 
	rm -f *.o
	rm -f 1a
	rm -f 1b
	rm -f 1c
	rm -f bcmp
