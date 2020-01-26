#include <stdio.h>

extern unsigned int my_atoi(char c);

int main(int argc, char** argv)
{
    char c;
    c = getc(stdin);
    while(c != EOF)
    {
        if (c != '\n')
            fprintf(stdout,"%u " ,my_atoi(c));
        else
            fprintf(stdout, "\n");
        c = getc(stdin);
    }
    return 0;
}