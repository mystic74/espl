#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
    int pipefd[2];
    pid_t cpid;
    char buf;
    if (argc != 2)
    {
        printf("Error");
        exit(EXIT_FAILURE);
    }
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    cpid = fork();
    if (cpid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid > 0)
    {
        while (read(pipefd[0], &buf, 1) > 0)
            write(1, &buf, 1);
        write(1, "\n", 1);
        exit(EXIT_SUCCESS);
    }
    else
    {
        write(pipefd[1], argv[1], strlen(argv[1]));
        close(pipefd[1]);
        exit(EXIT_SUCCESS);
    }

    return 0;
}
