#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    int ABtoC[2];
    pipe(ABtoC);

    if (fork() > 0)
    {
        // Process A
        close(ABtoC[0]);
        dup2(ABtoC[1], STDOUT_FILENO);
        close(ABtoC[1]);     // Close this too!
        // Process A writing to C
        fprintf(stderr,"Hello, i'm child (pid %d)\n", (int)getpid());
        char* myargs[2];
        myargs[0] = strdup("ls");
        myargs[1] = strdup("-l\0");
        myargs[2] = NULL;

        execvp(myargs[0], myargs);


        _exit(1);
    }
    else
    {
        close(ABtoC[1]);
        /* code */
    }
    
    if (fork() > 0)
    {
        char buffer[100];
        ssize_t nbytes;
        close(ABtoC[1]);
        dup2(ABtoC[0], STDIN_FILENO);
        close(ABtoC[0]);
        fprintf(stderr,"Hello, i'm child (pid %d) reprinting\n", (int)getpid());

        char* myargs[2];
        myargs[0] = strdup("tail");
        myargs[1] = strdup("-n 2");
        myargs[2] = NULL;
        execvp(myargs[0], myargs);
        _exit(1);

        // Process C reading from both A and B
        /*while ((nbytes = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0)
        {
            
            write(STDOUT_FILENO, buffer, nbytes);
        }*/
    }
    else
    {
    
        close(ABtoC[0]);
        /* code */
    }
    wait(NULL); 
    return(0);
}