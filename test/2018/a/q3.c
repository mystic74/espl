#include <stdio.h>


void binary_printer(char input)
{
	int c;
	unsigned char bit;
	for (c = 7; c >= 0; c--)
	{
		bit = input & (1 << c);
		printf("%d", bit);
	}
}

void main()
{
	binary_printer('s');
}
