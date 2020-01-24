#include <stdio.h>

typedef struct my_type{
    int i;
    int j;

}my_type;

int main(int argc, char** argv)
{
    my_type x[5];
    printf("%d\n", &(x[4].i) - &(x[0].j));
    return 0;
}