#include <stdio.h>
void quad (void *p)
{
    (*p) = (*p)*(*p);
}

int main(){
    int i = 4;
    int *p1 = &i;
    quad(p1);
    printf("%d\n", i);
    return 0;
}
