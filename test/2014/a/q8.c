#include <stdio.h>
char* func(unsigned int num1, int num2){
    static char buff[33];
    char* ptr = &buff[sizeof(buff)-1];
    *ptr = '\0';
    do
    {
        *--ptr = "0123456789abcdef"[num1%num2];
        num1 /= num2;
    }while(num1 != 0);
    return ptr;
}

int main()
{
    printf("%s\n",func(16,16));
}
