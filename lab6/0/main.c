#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#include "LineParser.h"

#define MAX_INPUT 2048 

void curr_dir()
{
    char buf[MAX_ARGUMENTS];
    if (getcwd(buf, sizeof(buf)) == NULL)
        perror("getcwd() error");
    else
        printf("%s: ", buf);
}

int cd_impl(cmdLine *parsedLine)
    {
    if (chdir(parsedLine->arguments[1]) == -1)
    {
        perror("Failed to change dir");
    }
    return 1;
}

int main(int argc, char **argv)
{
    /* Change to const */
    char input[MAX_INPUT];
    pid_t cpid = 0;
    int status = 0;
    cmdLine *parsedLine = NULL;

    while (1)
    {
        curr_dir();
        fgets(input, MAX_INPUT, stdin);
        if (strcmp(input, "quit\n") == 0)
            break;

        parsedLine = parseCmdLines(input);
        cpid = fork();

        /* In the child scope*/
        if (cpid == 0)
        {
            printf("%d", execvp(parsedLine->arguments[0], parsedLine->arguments));
            _exit(1);
        }
        /* In parent scope, wait for death i guess.*/
        else
        {
            if (strcmp(parsedLine->arguments[0], "cd") == 0)
            {
                cd_impl(parsedLine);
            }
            else
            {
                waitpid(-1, &status, 0);
        }
            freeCmdLines(parsedLine);
        }
    }
    return 1;
}