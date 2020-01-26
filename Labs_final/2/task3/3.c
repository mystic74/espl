#include <stdio.h>
#include <stdlib.h>

#define MAX_BUF 10

typedef struct fun_desc {
  char *name;
  void (*fun)(char*);
}my_func;

extern void string_reader(char* s);
extern void echo_printer(char* c); /* task 0 from lab1 - prints c to the standard output*/
extern void ascii_printer(char* c); /* task 1a from lab1 - convert a char to its ascii code and print it to the standard output*/
extern void binary_printer(char* c); /*task 1b from lab1 - convert a char to its ascii code in binary (least significant bit to the most 
                               significant representation) and print it to the standard output */
extern void upper_to_lower_to_upper_printer(char* c); /* task 1c from lab1 - convert to upper case letters if the input is lower case letters and vice versa*/
extern void string_printer(char *array, void (*f) (char*));
extern void bitwise_xor(char* s);


enum PRINTER_OPTIONS
{
	PRINTER_ECHO,
	PRINTER_ASCII,
	PRINTER_BINARY,
	PRINTER_UP_LOW,
	PRINTER_XOR,
	PRINTERS_AMOUNT
};

int main()
{
	my_func func_pointers[PRINTERS_AMOUNT];
	char my_buf[MAX_BUF];	
	char option_chosen;

	/* Init function pointers and names*/
	func_pointers[PRINTER_ECHO].name = "echo printer";
	func_pointers[PRINTER_ECHO].fun = echo_printer;

	func_pointers[PRINTER_ASCII].name = "ascii printer";
	func_pointers[PRINTER_ASCII].fun = ascii_printer;

	func_pointers[PRINTER_BINARY].name = "binary printer";
	func_pointers[PRINTER_BINARY].fun = binary_printer;

	func_pointers[PRINTER_UP_LOW].name = "upper to lower and lower to upper case";
	func_pointers[PRINTER_UP_LOW].fun = upper_to_lower_to_upper_printer;

	func_pointers[PRINTER_XOR].name = "bitwise xor";
	func_pointers[PRINTER_XOR].fun = bitwise_xor;

	printf("Please enter a string (0<size<=10):\n");
	string_reader(my_buf);

	printf("Please choose printer type:\n%d)%s\n%d)%s\n%d)%s\n%d)%s\n%d)%s\n",
			PRINTER_ECHO, func_pointers[PRINTER_ECHO].name,
			PRINTER_ASCII, func_pointers[PRINTER_ASCII].name,
			PRINTER_BINARY, func_pointers[PRINTER_BINARY].name,
			PRINTER_UP_LOW, func_pointers[PRINTER_UP_LOW].name,
			PRINTER_XOR, func_pointers[PRINTER_XOR].name);

	option_chosen = getc(stdin);

	while (option_chosen != EOF)
	{
		/* Using unsigned to surpass the under zero check */
		if (((unsigned int)atoi(&option_chosen)) >= PRINTERS_AMOUNT)
			printf("%c is not a valid option, Please choose from the menu \n", option_chosen);
		else if (option_chosen == '\n')
		{

		}
		else /* Valid input*/
		{
			printf("Option : %c\n", option_chosen);
			if (atoi(&option_chosen) == PRINTER_XOR)
				func_pointers[atoi(&option_chosen)].fun(my_buf);
			else
				string_printer(my_buf, func_pointers[atoi(&option_chosen)].fun);
		}
		option_chosen = getc(stdin);		

	}

	printf("Option : DONE.\n");

	return 0;

}