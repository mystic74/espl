#include <stdio.h>

void char2asciia()
{
    char c;
    while ((c=fgetc(stdin)) != EOF)
    {
        if (c != 10)
        {
            printf("%d", c);
        }
    }
}

int main()
{
    char2asciia();
    return 0;
}
