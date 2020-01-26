#include <stdio.h>
#include <string.h>


#define MAX_BUF 10

void PrintHex(unsigned char* buffer, unsigned int length)
{
	unsigned int index = 0;

	for (index = 0; index < length; index++)
	{
		printf("%02x ", buffer[index]);
	}
}


int main(int argc, char** argv)
{
	FILE* inputfile = NULL;
	unsigned char input_buf[MAX_BUF];
	unsigned int input_length = 0;
	if (argc != 2)
	{
		printf("Wrong number of arguments, should be 2\n");
		printf("Usage is:\n");
		printf("%s <filename>\n", argv[0] );
		return 1;
	}

	/* Try to open the file*/
	inputfile = fopen(argv[1], "r");

	do
	{
		input_length = fread(input_buf, sizeof(unsigned char), MAX_BUF, inputfile);
		PrintHex(input_buf, input_length);
	} while(input_length == MAX_BUF);

	printf("\nDone. \n");
}