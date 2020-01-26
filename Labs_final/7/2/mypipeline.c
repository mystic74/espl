#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

enum PIPE_INDEX
{
    IN_FILE,
    OUT_FILE,
    FILE_TYPES_NUM
};

void my_print(const char* str, int debug_mode)
{
    if (debug_mode)
    {
        printf("%s \n", str);
    }
}

int main(int argc, char** argv)
{
    int AtoB[FILE_TYPES_NUM];
    pipe(AtoB);
    int debug_mode = 0;
    int running_index = 0;
    int i = 0;
    int status;
    /* Two children */
    int cpid[2] = {0,0};
    if (argc > 1)
    {
        for (running_index = 1; running_index < argc; running_index++)
        {
            if (strcmp(argv[running_index], "-d") == 0)
            {
                debug_mode = 1;
            }
        }
    }
    my_print("parent_process>forking…", debug_mode);
    cpid[0] = fork();
    if (cpid[0] == 0)
    {

        close(AtoB[IN_FILE]);
        my_print("child1>redirecting stdout to the write end of the pipe…", debug_mode);
        dup2(AtoB[OUT_FILE], STDOUT_FILENO);
        close(AtoB[OUT_FILE]);
        char* myargs[2];
        myargs[0] = strdup("ls");
        myargs[1] = strdup("-l\0");
        myargs[2] = NULL;
        my_print("child1>going to execute cmd: …", debug_mode);
        execvp(myargs[0], myargs);


        _exit(1);
    }
    else
    {
        if (debug_mode)
        {
            printf("%s %d \n", "parent_process>created process with id:", cpid[0]);
        }

        my_print("parent_process>closing the write end of the pipe…", debug_mode);
        close(AtoB[OUT_FILE]);
        /* code */
    }
    
    cpid[1] = fork();
    if (cpid[1] == 0)
    {
        close(AtoB[OUT_FILE]);
        my_print("child1>redirecting stdin to the read end of the pipe…", debug_mode);
        dup2(AtoB[IN_FILE], STDIN_FILENO);
        close(AtoB[IN_FILE]);

        char* myargs[2];
        myargs[0] = strdup("tail");
        myargs[1] = strdup("-n 2");
        myargs[2] = NULL;

        my_print("child2>going to execute cmd: …", debug_mode);
        execvp(myargs[0], myargs);
        _exit(1);

    }
    else
    {
        if (debug_mode)
        {
            printf("%s %d \n", "parent_process>created process with id:", cpid[1]);
        }
        my_print("parent_process>closing the read end of the pipe…", debug_mode);
        close(AtoB[IN_FILE]);
        /* code */
    }
    my_print("parent_process>waiting for child processes to terminate…", debug_mode);
    for (i = 0; i < 2; i++)
    {
        waitpid(cpid[i], &status, 0);
    }
    return(0);
}