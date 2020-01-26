#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <linux/limits.h>

/*#include "list_utils.c"*/

#include "LineParser.h"

#define list_size 5
#define MY_MAX_INPUT 2048 
#define MAX_CHILDS 300

int arg_shifter(cmdLine* mycommand);

/* 1d */
char* home_replacer(const char* curr_str)
{
    char*  newpath;
    char* pathvar = getenv("HOME");
    unsigned int index = 0;
    const char* last_tilda = NULL;

    if (curr_str[0] == 126)
        last_tilda = curr_str;
    
    if (last_tilda == NULL)
        return NULL;

    else
    {
        newpath = (char*)malloc(PATH_MAX);
        newpath[0] = 0;
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
    if (mycommand == NULL)
        return 1;

    for (index = 0 /* 1 or 0? */ ; index < mycommand->argCount; index++)
    {
        replaceStr = home_replacer(mycommand->arguments[index]);

        if (replaceStr != NULL)
        {
            replaceCmdArg(mycommand, index, replaceStr);
            free(replaceStr);
        }
        
        
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
    char input[MY_MAX_INPUT] = {};
    pid_t cpid = 0;
    int status = 0;
    cmdLine *parsedLine = NULL;
    int err = 0;
    while (1)
    {
        curr_dir();
        fgets(input, MY_MAX_INPUT, stdin);
        if (strcmp(input, "quit\n") == 0)
            break;

        parsedLine = parseCmdLines(input);
        arg_shifter(parsedLine);
    
        if (strcmp(parsedLine->arguments[0], "cd") == 0)
        {
            cd_impl(parsedLine);
        }
        else
        {
           
            cpid = fork();

            /* In the child scope*/
            if (cpid == 0)
            {
                
                err = execvp(parsedLine->arguments[0], parsedLine->arguments);

                if (err == -1)
                {
                    perror("Failed to execvp\n");
                }
                _exit(1);
            }
            /* In parent scope, wait for death i guess.*/
            else
            {
                if (parsedLine->blocking)
                {
                    waitpid(cpid, &status, 0);
                }
            }
        }
        
        freeCmdLines(parsedLine);
    }
    return 1;
}