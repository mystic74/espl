#include <stdio.h> 
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>

/* Non blocking */
 #define _GNU_SOURCE             /* See feature_test_macros(7) */
       #include <fcntl.h>              /* Obtain O_* constant definitions */
       #include <unistd.h>
char* msg1 = "hello"; 
char* first_cmd = "ls";
char* second_cmd = "tail";

char* second_cmd_args[] = {"-n\0", "2\0"};

void execute_ls(int p[2]);
void execule_tail(int p[2]);

int replace_stdout(int new_file_fd);
int replace_stdin(int new_file_fd);


enum PROCESSS
{
    LS_PROC,
    TAIL_PROC,
    NUM_OF_PROC
};
void (*funcs[])(int p[2]) = {execute_ls, execule_tail};

void execute_ls(int p[2])
{
    int r_val;
    fprintf(stderr,"(child1>redirecting stdout to the write end of the pipe…)\n");
    replace_stdout(p[0]);
    fprintf(stderr, "(child1>going to execute cmd: …)\n");

    printf("Hello, i'm child (pid %d)\n", (int)getpid());

    char* myargs[2];
    myargs[0] = strdup("ls");
    myargs[1] = strdup("-l\0");
    myargs[2] = NULL;
    
 /*   execvp(myargs[0], myargs);
    */
   write(STDOUT_FILENO, "Hi\n", sizeof("Hi\n"));    
}

void execule_tail(int p[2])
{
    
    int r_val;
    fprintf(stderr, "(child2>redirecting stdin to the read end of the pipe…)\n");
    replace_stdin(p[1]);
    fprintf(stderr, "(child2>going to execute cmd: …)\n");
    
    
    /*r_val = execvp(second_cmd, second_cmd_args);*/
    char* myargs[3];
    myargs[0] = strdup("tail");
    myargs[1] = strdup("-n 2");
    myargs[2] = NULL;
    myargs[3] = NULL;
    
    _exit(1);
    
}

int replace_stdout(int new_file_fd)
{
    /*close(STDOUT_FILENO);*/
    dup2(new_file_fd, STDOUT_FILENO);
    close(new_file_fd);
    return 1;
}

int replace_stdin(int new_file_fd)
{
    /*close(STDIN_FILENO);*/
    dup2(new_file_fd, STDIN_FILENO);
    close(new_file_fd);
    return 1;
}

/*
Will imitate the ls -l | tail -n 2 here..
*/
int main(int argc, char** argv) 
{ 
    int fork_num = 0;
    int p[2], pid, nbytes; 
    fd_set set;
    int rv;
    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 10000;
    int debug = 0;
    FD_ZERO(&set); /* clear the set */
  
    /* Non Blocking... 
    if (pipe2(p, O_NONBLOCK) < 0) 
        exit(1); 
    */
    if (argc > 0)
    {
        debug = 1;
    }
    if (pipe(p) < 0) 
        exit(1); 
    
    while (fork_num < NUM_OF_PROC)
    {
        fprintf(stderr,"forking... %d %d\n", fork_num, NUM_OF_PROC);
        if ((pid = fork()) > 0)
        {
            fprintf(stderr,"main proc\n");
            close(p[fork_num]);
        }   
        else if (pid == 0)
        {   fprintf(stderr,"Son Proc\n");
            funcs[fork_num](p);
            _exit(1);
            fprintf(stderr,"Son Proc done?...\n");
            break;
        } 
        else
        {
            perror("Fork error");
        }

        fork_num++;        
    }

     wait(NULL); 

    return 0; 
}