#include <stdio.h>
extern int func(int* a, int* b, int* c);
int main()
{
    int a=1, b=2, c=3, d;
    d = func(&a, &b, &c);
    printf("%d\n",d);
    return 0;
}