#ifndef _PIPES_UTILS_H
#define _PIPES_UTILS_H
#include "LineParser.h"
#include <unistd.h>

typedef struct pipe_fds
{
    int p[2];
}pipe_fds;

pipe_fds** generate_pipes_arr(unsigned int length);
void free_pipes_arr(pipe_fds** pipes, unsigned int amount_of_cmds);
pipe_fds *leftPipe(pipe_fds **pipes, cmdLine *pCmdLine);
pipe_fds *rightPipe(pipe_fds **pipes, cmdLine *pCmdLine);
#endif