// C program to illustrate 
// pipe system call in C 
// shared by Parent and Child 
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
  
int main() 
{ 
    char inbuf[strlen(msg1) + 1]; 
    int p[2], pid, nbytes; 
    fd_set set;
    int rv;
    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 10000;

    FD_ZERO(&set); /* clear the set */
  
    /* Non Blocking... 
    if (pipe2(p, O_NONBLOCK) < 0) 
        exit(1); 
    */
    
    if (pipe(p) < 0) 
        exit(1); 
    
    /* continued */
    if ((pid = fork()) > 0) { 
    
        FD_SET(p[0], &set); /* add our file descriptor to the set */
        rv = select(p[0] + 1, &set, NULL, NULL, &timeout);

        if(rv == -1)
            perror("select"); /* an error accured */
        else if(rv == 0)
            printf("timeout"); /* a timeout occured */
        else
        {
            nbytes = read(p[0], inbuf, strlen(msg1));
            printf("%s\n", inbuf); 

            /*while ( nbytes > 0) 
            {
                printf("%s\n", inbuf); 
                nbytes = read(p[0], inbuf, strlen(msg1));
            }*/
        }
        if (nbytes != 0) 
            exit(2); 
        printf("Finished reading\n"); 
         
       
        // Adding this line will 
        // not hang the program 
        // close(p[1]); 
       
    } 
    /* Child scope */
    else if (pid == 0) { 
        // Adding this line will 
        // not hang the program 
        // close(p[1]);
        
 
        write(p[1], msg1, strlen(msg1)); 
        printf("Finished writing\n"); 

        exit(2); 
    } 

     wait(NULL); 

    return 0; 
}