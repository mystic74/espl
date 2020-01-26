#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
int main(int argc, char **argv)
{
    if (!fork() || fork())
    {
        printf("+");
        exit(0);
    }
    return 0;
}