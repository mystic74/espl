#include "pipes_utils.h"
#include <stdlib.h>

pipe_fds** generate_pipes_arr(unsigned int length)
{
    pipe_fds** pipes = (pipe_fds**)malloc(length * sizeof(pipe_fds*));

    int i;
    for (i = 0; i < length; i++)
    {
        
        pipe_fds* curr_pipe = (pipe_fds *)malloc(sizeof(pipe_fds));
        pipe(curr_pipe->p);
        pipes[i] = curr_pipe;
    }

    return pipes;
}

void free_pipes_arr(pipe_fds** pipes, unsigned int amount_of_cmds)
{
    unsigned int index;
    for (index = 0; index < amount_of_cmds; index++)
    {
            free(pipes[index]);
            pipes[index] = NULL;
    }
    free(pipes);
}

pipe_fds* leftPipe(pipe_fds** pipes, cmdLine* pCmdLine)
{
    if (pCmdLine->idx == 0)
        return NULL;

    return pipes[pCmdLine->idx - 1];
}

pipe_fds* rightPipe(pipe_fds** pipes, cmdLine* pCmdLine)
{
    if (!pCmdLine->next)
        return NULL;

    return pipes[pCmdLine->idx];
}