#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {if (fork() + fork()) printf("===%d, Parent%d=== Bingo!\n", getpid(), getppid());
return 0;
}
