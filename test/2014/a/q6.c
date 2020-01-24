#include <stdio.h>
int main()
{
    int** p;
    printf("%d", ((int)(p)) - (int)p);
    printf("%d", ((int)(p+ sizeof(int*))) - (int)p);
    return 0;
}
