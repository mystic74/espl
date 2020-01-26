#include <stdio.h>


#define MAX_BUFFER 10000

int main(int argc, char **argv)
{
    int i = 0;
    for (i = 1; i < argc; i++)
    {
        printf("%s ", argv[i]);
    }

    printf("\n");
    return 0;
}
