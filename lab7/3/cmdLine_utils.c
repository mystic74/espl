#include "LineParser.h"
unsigned int get_cmd_command_count(cmdLine* firstCmd)
{
    unsigned int amount = 0;
    cmdLine* currCmd = firstCmd
    while(currCmd != NULL)
    {
        amount++;
        currCmd = currCmd->next;
    }
    
    return amount;
}