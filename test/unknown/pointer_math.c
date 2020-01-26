#include <stdio.h>

int main(int argc, char **argv)
{
    int x = 10;

    printf("sizeof long pointer : %x, long pointer : %p, next point : %p int jump : %X \n",
           sizeof(long *), (long *)&x, (((long *)&x) + 1), (((long *)&x) + 1) - (long *)&x);
    printf("sizeof int pointer : %x, int pointer : %p, next point : %p int jump : %X \n",
           sizeof(int *), (int *)&x, (((int *)&x) + 1), (((int *)&x) + 1) - (int *)&x);
    printf("sizeof short pointer : %x, short pointer : %p, next point : %p short jump : %X \n",
           sizeof(short *), (short *)&x, (((short *)&x) + 1), (((short *)&x) + 1) - (short *)&x);
    printf("sizeof char pointer : %x, char pointer : %p, next point : %p char jump : %X \n",
           sizeof(char *), (char *)&x, (((char *)&x) + 1), (((char *)&x) + 1) - (char *)&x);
    printf("sizeof void pointer : %x, void pointer : %p, next point : %p void jump : %X \n",
           sizeof(void *), (void *)&x, (((void *)&x) + 1), (((void *)&x) + 1) - (void *)&x);
    return 0;
}