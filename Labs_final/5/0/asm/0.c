#include <stdio.h>

/* For errors and stuff.*/
#include <errno.h>
#include <string.h>

#define O_RDONLY 00000000

extern int my_open(int nsyscall, char *filename, int flags);
extern int my_close(int fd);

int main(int argc, char **argv)
{
    int errsv;
    if (argc < 2)
    {
        printf("min 2 argumetns. \n");
        printf("%s <file to check> \n", argv[0]);
    }

    int fd = my_open(5, argv[1], O_RDONLY);
    if (fd == -1)
    {
        errsv = errno;
        printf("Open failed with error %s \n", strerror(errsv));
    }

    printf("File opened, fd value is %d \n", fd);

    if (my_close(fd) == -1)
    {
        errsv = errno;
        printf("Close failed with error %s \n", strerror(errsv));
    }
    else
    {
        printf(" CLOSING DONE\n");
    }
}