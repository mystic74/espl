#include <stdio.h>

extern unsigned char *utoa_s(unsigned int number_numnum);

int main(int argc, char **argv)
{

    fprintf(stdout, "%s", utoa_s(112233));

    fprintf(stdout, "%s", utoa_s(-1));

	fprintf(stdout, "%s", utoa_s(123));
    return 0;
}