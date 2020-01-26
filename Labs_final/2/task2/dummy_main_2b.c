extern void echo_printer(char* c); /* task 0 from lab1 - prints c to the standard output*/
extern void ascii_printer(char* c); /* task 1a from lab1 - convert a char to its ascii code and print it to the standard output*/
extern void binary_printer(char* c); /*task 1b from lab1 - convert a char to its ascii code in binary (least significant bit to the most 
                               significant representation) and print it to the standard output */
extern void upper_to_lower_to_upper_printer(char* c); /* task 1c from lab1 - convert to upper case letters if the input is lower case letters and vice versa*/

extern void string_printer(char *array, void (*f) (char*));

int main()
{
	char c[] = {'L','a','b','2','\0'};
    string_printer(c,ascii_printer);
	return 0;
}