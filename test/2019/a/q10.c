#include <stdio.h>

struct node
{
    int data;
    struct node *next;
};

int main(int argc, char **argv)
{
    char x1[] = "a";
    static struct node x2;

    if ((unsigned long)x1 > (unsigned long)&argv)
        printf("a");
    else
    {
        printf("b");
    }

    if ((unsigned long)main < (unsigned long)&x2)
        printf("c");
    else
    {
        printf("d");
    }

    if ((unsigned long)&x1 <= (unsigned long)x1)
        printf("e");
    else
    {
        printf("f");
    }

    return 0;
}