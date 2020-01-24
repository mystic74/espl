#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    unsigned int num=5;
    int i;
    for (i=0; i<8; i++)
    {
        printf("%d", (num << i & argc << 6)? 1: 0);
    }
    printf("\n");
    return 0;
}
