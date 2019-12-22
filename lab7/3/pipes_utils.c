#include "pipes_utils.h"
#include <stdlib.h>

int** generate_pipes_arr(unsigned int length)
{
    int** pipes = (int**)malloc(length * sizeof(int*));

    int i;
    for (i = 0; i < length; i++)
    {
        
        int* curr_pipe = (int *)malloc(sizeof(int) * 2);
        pipe(curr_pipe);
        pipes[i] = curr_pipe;
    }

    return pipes;
}

void free_pipes_arr(int** pipes, unsigned int amount_of_cmds)
{
    unsigned int index;
    for (index = 0; index < amount_of_cmds; index++)
    {
            free(pipes[index]);
            pipes[index] = NULL;
    }
    free(pipes);
}

int* leftPipe(int** pipes, cmdLine* pCmdLine)
{
    if (pCmdLine->idx == 0)
        return NULL;

    return pipes[pCmdLine->idx - 1];
}

int* rightPipe(int** pipes, cmdLine* pCmdLine)
{
    if (!pCmdLine->next)
        return NULL;

    return pipes[pCmdLine->idx];
}