#include <stdio.h>
#include <stdlib.h>

int main (int argc, char** argv)
{
	char* str = "The big fox hid the carrots";
	char* i = (char*)( str+ 2*sizeof(str));
	/*int* i = (int*)(str + 2*sizeof(str));*/
	printf("%s\n", (char*)i);
	return 0;
}
