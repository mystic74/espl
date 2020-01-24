#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv){
    if (*argv && !fork())
    {
        execvp(*argv, argv);
        printf("%s", argv[1]);
    }
    else
    {
        execvp(*argv, (++argv));
        printf("%s", argv[0]);
    }
    
    return 0;
}