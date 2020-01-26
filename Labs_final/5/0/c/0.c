#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

/* For errors and stuff.*/
#include <errno.h>
#include <string.h>
int main(int argc, char **argv)
{
    int errsv;
    if (argc < 2)
    {
        printf("min 2 argumetns. \n");
        printf("%s <file to check> \n", argv[0]);
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        errsv = errno;
        printf("Open failed with error %s \n", strerror(errsv));
    }

    printf("File opened, fd value is %d \n");

    if (close(fd) == -1)
    {
        errsv = errno;
        printf("Close failed with error %s \n", strerror(errsv));
    }
    else
    {
        printf(" CLOSING DONE\n");
    }
}