#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <linux/limits.h>

#include "LineParser.h"

#define MAX_INPUT 2048 

char* home_replacer(const char* curr_str)
{
    char*  newpath;
    char* pathvar = getenv("HOME");
    unsigned int index = 0;
    char* last_tilda = NULL;
    /*last_tilda = strrchr(curr_str, 126);*/
    if (curr_str[0] == 126)
        last_tilda = curr_str;
    
    if (last_tilda == NULL)
        return NULL;

    else
    {
        newpath = (char*)malloc(PATH_MAX);
        strcat(newpath, pathvar);
        index = strlen(pathvar);
        last_tilda++; /* Go over the ~*/ 
        while(*last_tilda != '\0')
        {
            newpath[index] = *last_tilda;
            index++;
            last_tilda++;
        }
        return newpath;
    }
}

int arg_shifter(cmdLine* mycommand)
{
    int index = 0;
    char* replaceStr; 
    for (index = 1 /* 1 or 0? */ ; index < mycommand->argCount; index++)
    {
        replaceStr = home_replacer(mycommand->arguments[index]);
        if (replaceStr != NULL)
            replaceCmdArg(mycommand, index, replaceStr);
    }

    return 1;
}
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
        arg_shifter(parsedLine);
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