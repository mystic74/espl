#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <linux/limits.h>
#include <fcntl.h>
#include "list_utils.c"
#include "env_var_utils.h"
#include "LineParser.h"
#include "pipe_utils.h"

#define list_size 5
#define MY_MAX_INPUT 2048 
#define MAX_CHILDS 300

enum FILE_INDEX
{
    IN_FILE,
    OUT_FILE,
    FILE_TYPES_NUM
};

enum PIPE_INDEX
{
    PIPE_INPUT_END,
    PIPE_OUTPUT_END,
    NUM_OF_PIPE_ENDS
};

unsigned int get_cmd_command_count(cmdLine* firstCmd)
{
    unsigned int amount = 0;
    cmdLine* currCmd = firstCmd;
    while(currCmd != NULL)
    {
        amount++;
        currCmd = currCmd->next;
    }
    
    return amount;
}

/*
* cmd_line - the command were parsing
*
* io_flags - output parameter, so we can know if we opened a file or not.
*
* pipes - pipe array, if we need to redirect the output to the next command.
*/
void replace_io(cmdLine *cmd_line, char io_flags[], int** pipes) 
{
    int* left_pipe = leftPipe(pipes, cmd_line);
    int* right_pipe = rightPipe(pipes, cmd_line);
    /* io_flags is an out parameter to indicate if we opened a file (and need to close it.) */
    if (cmd_line->outputRedirect)
    {
        close(STDOUT_FILENO);
        dup2(open(cmd_line->outputRedirect, O_WRONLY | O_CREAT, 0777), STDOUT_FILENO);
        io_flags[OUT_FILE] = 1;
    }

    if (cmd_line->inputRedirect)
    {
        close(STDIN_FILENO);
        dup2(open(cmd_line->inputRedirect, O_RDONLY), STDIN_FILENO);
        io_flags[IN_FILE] = 1;
    }

     if (left_pipe != NULL)
    {
        #ifdef VERBOSE
        fprintf(stderr, "redirect comamnd %s's input to fd %d\n", cmd_line->arguments[0], left_pipe[0]); 
        #endif
        close(left_pipe[PIPE_OUTPUT_END]);
        close(STDIN_FILENO);
        dup2(left_pipe[PIPE_INPUT_END], STDIN_FILENO);
        close(left_pipe[PIPE_INPUT_END]);
    }

    if (right_pipe != NULL)
    {
        #ifdef VERBOSE
        fprintf(stderr, "redirect comamnd %s's output to fd %d\n", cmd_line->arguments[0], right_pipe[0]);
        #endif
        close(right_pipe[PIPE_INPUT_END]);
        close(STDOUT_FILENO);
        dup2(right_pipe[PIPE_OUTPUT_END], STDOUT_FILENO);
        close(right_pipe[PIPE_OUTPUT_END]);
    }
}


void close_files(char io_flags[])
{
    if (io_flags[IN_FILE])
        close(STDIN_FILENO);
    
    if (io_flags[OUT_FILE])
        close(STDOUT_FILENO);
}

char* dolla_replacer(const char* curr_str, pair_node* env_list)
{
    char*  newvar;
    unsigned int index = 0;
    pair_node* tempList = env_list;
    const char* last_dolla = NULL;


    last_dolla = strchr(curr_str, 36);

    /* If its null, no dollar sign.*/
    if (last_dolla == NULL)
        return (char*)curr_str;

    newvar = (char*)malloc(MY_MAX_INPUT);
    newvar[0] = 0;

    for (index = 0; index < strlen(curr_str); index++)
    {
        if (*(curr_str + index) == 36)
        {
            tempList = env_list;
            /* were here, so we have a $ somewhere. lets go over all args and check if hes valid*/
            /* Go over the list, and compare to the value given.
                if equals, print.*/
            while(tempList != NULL)
            {
                if (strcmp(tempList->curr_var->name, last_dolla + 1) == 0)
                {
                    strcat(newvar, tempList->curr_var->value);
                    break;
                }
                tempList = tempList->next;
            }                
        }
    }
    
    return newvar;
}
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
int arg_shifter(cmdLine* mycommand, node* command_list, pair_node* env_list)
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
        if (replaceStr == mycommand->arguments[index])
        {
            replaceStr = dolla_replacer(mycommand->arguments[index], env_list);
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
    int command_index = 0;
    cmdLine *parsedLine = NULL;
    cmdLine* orgLine = NULL;
    node* command_list = NULL;
    pair_node* env_var_list = NULL;
    pair* temp_pair = NULL;
    command_list = alloc_list_size(list_size);
    int arg_rval = 0;
    char io_flags[FILE_TYPES_NUM] = {0, 0};

    int curr_cmds_in_line = 0;
    int** command_pipes = NULL;
    int* curr_children = NULL;
    int child_index = 0;
    int inner_action;
    int tempstatus = 0;

    while (1)
    {
        inner_action = 1;
        curr_dir();
        fgets(input, MY_MAX_INPUT, stdin);
        if (strcmp(input, "quit\n") == 0)
            break;

        parsedLine = parseCmdLines(input);
        orgLine = parsedLine;
        arg_rval = arg_shifter(parsedLine, command_list, env_var_list);
    
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

        /* Task 3 changes, adding the command queue thingy*/
        curr_cmds_in_line = get_cmd_command_count(parsedLine);
        /*Generate pipes so the every process enters on one end and exists on the other.*/
        command_pipes = generate_pipes_arr(curr_cmds_in_line);
        /* Each commands might have a process, we need to follow up on them.*/
        curr_children = (int*)malloc(sizeof(int) * curr_cmds_in_line);

        if (strcmp(parsedLine->arguments[0], "cd") == 0)
        {
            cd_impl(parsedLine);
            freeCmdLines(parsedLine);
            continue;
        }
        else if (strcmp(parsedLine->arguments[0], "history") == 0)
        {
            if ((parsedLine->argCount > 1) && (strcmp(parsedLine->arguments[1], "-d") == 0))
            {
                command_list = remove_node_at_index(command_list, atoi(parsedLine->arguments[2]));
            }
        }
        else if  (strcmp(parsedLine->arguments[0], "set") == 0)
        {
            temp_pair = get_node_from_name(env_var_list, parsedLine->arguments[1]);
            /* Check for existing argument*/
            if (temp_pair != NULL)
            {
                free(temp_pair->value);

                /* Updating the value from the arguments*/
                temp_pair->value = (char*) malloc(strlen(parsedLine->arguments[2]) + 1);
                memcpy(temp_pair->value, parsedLine->arguments[2], strlen(parsedLine->arguments[2]));
                temp_pair->value[strlen(parsedLine->arguments[2]) + 1] = 0;
            }
            else
            {
              temp_pair = generate_pair(parsedLine->arguments[1], parsedLine->arguments[2]);
              env_var_list = env_list_append(env_var_list, temp_pair);
            }
            freeCmdLines(parsedLine);

            continue;
        }
        else if  (strcmp(parsedLine->arguments[0], "env") == 0)
        {
            print_env_for_val(env_var_list, parsedLine->arguments[1]);
            continue;
        }
        else if  (strcmp(parsedLine->arguments[0], "delete") == 0)
        {
            env_var_list = remove_env_name(env_var_list, parsedLine->arguments[1]);
            freeCmdLines(parsedLine);
            continue;
        }
        else
        {
            inner_action = 0;
        }

        /* Run this in a loop for each sub command...*/
        for (child_index = 0; child_index < curr_cmds_in_line; child_index++)
        {
            #ifdef VERBOSE
            fprintf(stderr, "run number  %d \n", child_index);
            #endif
            cpid = fork();

            /* In the child scope*/
            if (cpid == 0)
            {
                replace_io(parsedLine, io_flags, command_pipes);

                if (!inner_action)
                {

                    #ifdef VERBOSE
                    fprintf(stderr, "execvp for %s \n", parsedLine->arguments[0]);
                    fprintf(stdout, "execvp for %s  stdout\n", parsedLine->arguments[0]);
                    #endif

                    printf("%d", execvp(parsedLine->arguments[0], parsedLine->arguments));


		            #ifdef VERBOSE
                    fprintf(stderr, "erasing cmd  %s in child process \n", parsedLine->arguments[0]);
                    #endif

                    freeCmdLines(parsedLine);

                }
                else
                {
                    #ifdef VERBOSE
                    fprintf(stderr, "execvp for %s \n", parsedLine->arguments[0]);
                    fprintf(stdout, "execvp for %s  stdout\n", parsedLine->arguments[0]);
                    #endif
                    /* Only one for now... */
                    list_print(command_list,stdout);
                }
                
                /* Remove from failed process */
                close_files(io_flags);

                #ifdef VERBOSE
                fprintf(stderr, "erasing cmd  %s in child process \n", parsedLine->arguments[0]);
                #endif
                env_list_free(env_var_list);
                freeCmdLines(parsedLine);
                list_free(command_list);
                free_pipes_arr(command_pipes, curr_cmds_in_line);
                free(curr_children);
                _exit(1);
            }
            /* In parent scope, wait for death i guess.*/
            else
            {
                #ifdef VERBOSE
                fprintf(stderr, "execvp for %s with child %d\n", parsedLine->arguments[0], cpid);
                #endif
                close(command_pipes[child_index][1]);
                curr_children[child_index] = cpid;
                parsedLine = parsedLine->next;
            }
        }

        parsedLine = orgLine;

        while(parsedLine)
        {
            if(parsedLine->blocking)
            {
                waitpid(curr_children[parsedLine->idx], &tempstatus, 0);
            }
            parsedLine = parsedLine->next;
        }

        free_pipes_arr(command_pipes, curr_cmds_in_line);
        free(curr_children);
        
        /*  Outside the scopes of child\father so on.
            Just freeing to current command*/
        freeCmdLines(orgLine);
        command_index++;
    }
    /* Free general command list. */
    env_list_free(env_var_list);
    list_free(command_list);
    if(parsedLine)
        freeCmdLines(parsedLine);

    return 1;
}
