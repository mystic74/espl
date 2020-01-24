#include <stdio.h>

int foo()
{
    char str1[] = "tmp";
    char str2[] = "tmp";
    str1[0] = 'e';
    str2 = "emp";
    return strcmp(str1, str2);
}

int main()
{
    printf("%d", foo());
}