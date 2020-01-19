 
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

void curr_dir()
{
    char buf[MAX_ARGUMENTS];
    if (getcwd(buf, sizeof(buf)) == NULL)
        perror("getcwd() error");
    else
        printf("%s: ", buf);
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
    command* tmpCommand = NULL;

    while (1)
    {
        curr_dir();
        fgets(input, MY_MAX_INPUT, stdin);
        if (strcmp(input, "quit\n") == 0)
            break;

        parsedLine = parseCmdLines(input);
        arg_shifter(parsedLine, command_list);
    
        command_list = list_append(command_list, generate_command(input, command_index));


            
        printf("%d", execvp(parsedLine->arguments[0], parsedLine->arguments));

        
        
        freeCmdLines(parsedLine);
        command_index++;
    }
    list_free(command_list);
    return 1;
}