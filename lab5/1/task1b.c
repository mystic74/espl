#include <stdio.h>

extern unsigned char *utoa_s(unsigned int number_numnum);

int main(int argc, char **argv)
{

    fprintf(stdout, "%s \n", utoa_s(112233));

    return 0;
}