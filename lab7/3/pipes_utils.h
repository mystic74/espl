#ifndef _PIPES_UTILS_H
#define _PIPES_UTILS_H
#include "LineParser.h"
#include <unistd.h>



int** generate_pipes_arr(unsigned int length);
void free_pipes_arr(int** pipes, unsigned int amount_of_cmds);
int *leftPipe(int **pipes, cmdLine *pCmdLine);
int *rightPipe(int **pipes, cmdLine *pCmdLine);
#endif