extern void bitwise_xor(char* s);
extern void string_reader(char* s);

#define MAX_BUF 10


int main()
{
	char my_buf[MAX_BUF];
	string_reader(my_buf);
	bitwise_xor(my_buf);
	return 0;
}