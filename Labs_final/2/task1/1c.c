#include <stdio.h>

void print_addr()
{
	int iarray[3];
    char carray[3];

    printf("%p %p \n",iarray, iarray+1);
    
    printf("%p %p \n",carray, carray+1);
    
}


int main()
{
	print_addr();
	return 0;
}