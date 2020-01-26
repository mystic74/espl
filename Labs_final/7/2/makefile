DEBUG_FLAGS  := -g3


C_FLAGS 	 := $(DEBUG_FLAGS) -Wall -m32
LD_FLAGS	 := 

all : mypipeline

mypipeline : mypipeline.o
	gcc $(C_FLAGS) $(LD_FLAGS) -o mypipeline mypipeline.o

mypipeline.o : mypipeline.c
	gcc $(C_FLAGS) -c -o mypipeline.o mypipeline.c

.PHONY : clean

clean : 
	rm -f *.o
	rm -f mypipeline 
