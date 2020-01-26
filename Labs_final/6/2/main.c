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
        return (char*)curr_str;

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

char* exclamation_replacer(const char* curr_str, node* command_list)
{
    char*  nstring;
    char* tempstr;
    int index;
    if (curr_str[0] != 33)
        return (char*)curr_str;
    
    index = atoi(++curr_str);
    tempstr = get_string_for_index(command_list, index);

    if(tempstr == NULL)
    {
        return NULL;
    }    

    nstring = (char*) malloc(strlen(tempstr) + 2);
    nstring[0] = 0;
    strcat(nstring, tempstr);

    return (char*)nstring;
    
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
        /* If no need for change */
        if (replaceStr == mycommand->arguments[index])
        {
            replaceStr = exclamation_replacer(mycommand->arguments[index], command_list);
        }
        
        /* If no need for change */
        if ((replaceStr != mycommand->arguments[index]) && (replaceStr != NULL))
        {
            replaceCmdArg(mycommand, index, replaceStr);
            free(replaceStr);
        }
        else if (replaceStr == NULL)
            return -1;
        
        
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

command* generate_command(char* input, int number)
{
    command* rval = malloc(sizeof(command));
    rval->n_command_index = number;
    memcpy(rval->str, input, strlen(input));
    rval->str[strlen(input) - 1] = 0;

    return rval;
}

command* generate_command_from_cmdLine(cmdLine* input, int number)
{
    command* rval = malloc(sizeof(command));
    int index = 0;
    rval->str[0] = 0;
    rval->n_command_index = number;
    for ( index = 0; index < input->argCount; index++)
    {
        strcat(rval->str, input->arguments[index]);
        strcat(rval->str, " ");
    }
    rval->str[strlen(rval->str) - 1] = 0;    
    return rval;
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
    int arg_rval = 0;

    while (1)
    {
        curr_dir();
        fgets(input, MY_MAX_INPUT, stdin);
        if (strcmp(input, "quit\n") == 0)
            break;

        parsedLine = parseCmdLines(input);
        arg_rval = arg_shifter(parsedLine, command_list);
    
        if (arg_rval == -1)
        {
            /* Invalid arg*/
            freeCmdLines(parsedLine);
            continue;
        }
        /* Check for empty input.*/
        if(parsedLine == NULL)
            continue;

        /* Add command to history */
        /*command_list = list_append(command_list, generate_command(input, command_index));*/
        command_list = list_append(command_list, generate_command_from_cmdLine(parsedLine, command_index));

        if (strcmp(parsedLine->arguments[0], "cd") == 0)
        {
            cd_impl(parsedLine);
        }
        else if (strcmp(parsedLine->arguments[0], "history") == 0)
        {
            if ((parsedLine->argCount > 1) && (strcmp(parsedLine->arguments[1], "-d") == 0))
            {
                command_list = remove_node_at_index(command_list, atoi(parsedLine->arguments[2]));
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
                /* Remove from failed process */
                freeCmdLines(parsedLine);
                list_free(command_list);
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
        }
        
        /*  Outside the scopes of child\father so on.
            Just freeing to current command*/
        freeCmdLines(parsedLine);
        command_index++;
    }
    /* Free general command list. */
    list_free(command_list);
    return 1;
}