#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    if (!fork() || fork())
    {
        printf("===%d, Parent%d=== +\n  ", getpid(), getppid());
        exit(0);
    }
    return 0;
}
