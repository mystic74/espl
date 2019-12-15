#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <linux/limits.h>

#include "list_utils.c"

#include "LineParser.h"

#define list_size 5
#define MY_MAX_INPUT 2048 
#define MAX_CHILDS 300

char* home_replacer(const char* curr_str)
{
    char*  newpath;
    char* pathvar = getenv("HOME");
    unsigned int index = 0;
    const char* last_tilda = NULL;
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

char* exclamation_replacer(const char* curr_str, node* command_list)
{
    char*  nstring;
    char* tempstr;
    int index;
    if (curr_str[0] != 33)
        return NULL;
    
    index = atoi(++curr_str);
    tempstr = get_string_for_index(command_list, index);

    nstring = (char*) malloc(strlen(tempstr) + 2);

    strcat(nstring, tempstr);

    return nstring;
    
}
int arg_shifter(cmdLine* mycommand, node* command_list)
{
    int index = 0;
    char* replaceStr; 
    if (mycommand == NULL)
        return 1;

    for (index = 0 /* 1 or 0? */ ; index < mycommand->argCount; index++)
    {
        replaceStr = home_replacer(mycommand->arguments[index]);

        replaceStr = exclamation_replacer(mycommand->arguments[index], command_list);
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
    char input[MY_MAX_INPUT] = {};
    pid_t cpid = 0;
    int status = 0;
    int command_index = 0;
    cmdLine *parsedLine = NULL;
    node* command_list = NULL;
    command_list = alloc_list_size(list_size);

    while (1)
    {
        curr_dir();
        fgets(input, MY_MAX_INPUT, stdin);
        if (strcmp(input, "quit\n") == 0)
            break;

        parsedLine = parseCmdLines(input);
        arg_shifter(parsedLine, command_list);
        if (strcmp(parsedLine->arguments[0], "cd") == 0)
        {
            cd_impl(parsedLine);
        }
        else if (strcmp(parsedLine->arguments[0], "history") == 0)
        {
            if (strcmp(parsedLine->arguments[1], "-d") == 0)
            {
                command_list = node_removal(command_list, atoi(parsedLine->arguments[2]));
            }
            else
                list_print(command_list,stdout);
        }
        else
        {
        
            
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
                if (parsedLine->blocking)
                {
                    waitpid(-1, &status, 0);
                }
            }

            command_list = list_edit_at_loc_allocatec(command_list, input, command_index);
            freeCmdLines(parsedLine);
            command_index++;
        }
    }
    list_free(command_list);
    return 1;
}