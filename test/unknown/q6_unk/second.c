#include <stdio.h>
#include <stdlib.h>
int main(int argc, char** argv){
char buf[100];
fgets(buf, 100, stdin);
printf("%s", buf);
printf("%s\n", argv[1]);
}
