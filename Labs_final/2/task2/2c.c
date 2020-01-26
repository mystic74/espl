#include <stdio.h>


#define MAX_BUF 10

extern void binary_printer(char* c);

void bitwise_xor(char* s){
  int index = 0;
  char temp_sum = 0;

  while ((s[index] != '\0') && (index < MAX_BUF))
  {
  	if (s[index] != '\n')
  	{
  		temp_sum ^= s[index];
  	}
  	index++;
  }

  binary_printer(&temp_sum);
  printf("\n");
  printf("%x", temp_sum);
  printf("\n");

}

void string_reader(char* s){
  fgets(s, MAX_BUF, stdin);
}