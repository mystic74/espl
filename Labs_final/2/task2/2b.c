#include <stdio.h>

void string_printer(char *array, void (*f) (char*))
{
	int index = 0;
	while(array[index] != '\0')
	{
		if (array[index] != '\n')
			f(&(array[index]));
		index++;
	}

	printf("\n");
}


