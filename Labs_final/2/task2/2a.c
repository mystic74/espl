#include <stdio.h>
void echo_printer(char* c)
{
	if (c != NULL)
		printf("%c",*c);
}
void ascii_printer(char* c)
{
	if (c == NULL)
		return;

	printf("%d ", *c);
}

void binary_printer(char* c)
{
	int temp_num = 0;
	int index = 0;

	if (c == NULL)
		return;

	for (index = 0; index < 8; index++)
	{
		temp_num = (*c) >> index;
		if (temp_num & 1)
			printf("1");
		else
			printf("0");
	}
	printf(" ");
}

void upper_to_lower_to_upper_printer(char* c)
{
	if ((*c >= 'A') && (*c <='Z'))
		printf("%c", (*c) + ('a'-'A'));
	if ((*c >= 'a') && (*c <='z'))
		printf("%c", (*c) - ('a'-'A'));
}