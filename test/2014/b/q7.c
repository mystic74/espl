#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv){
    int p[2], pid, nbytes;
    char buffer[20];

    pipe(p);

    if ((pid == fork())){
        write(p[1], argv[0], strlen(argv[0]) + 1);
        write(p[1], argv[1], strlen(argv[1]) + 1);
    }

    close(p[1]);
    if ((nbytes = read(p[0], buffer, sizeof(buffer)))> 0)
    {
               printf("%s %u\n", buffer, pid);
    }
    return 0;
}