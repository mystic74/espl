#include <stdio.h>
#include <string.h>

#define BYTE_LENGTH 8

extern unsigned int my_atoi(char c);
extern char* atob(char c, char out_arr[BYTE_LENGTH]);
extern char change_letter_case(char c);

int main(int argc, char** argv)
{
    char c;
    int index;
    int to_bin = 0;
    int to_caps = 0;
    char output_arr[BYTE_LENGTH];
    FILE* output = stdout;

    for (index = 1; index < argc; index++)
    {
        if (strcmp("-b", argv[index]) == 0)
        {
            to_bin = 1;
        }
        if (strcmp("-c", argv[index]) == 0)
        {
            to_caps = 1;
        }
    }
    
    /* Gathering input like this (and not in do while) so i won't print the EOF. */
    c = getc(stdin);
    while(c != EOF)
    {
        if (c != '\n')
        {
            /* Setting the output in a buffer, null terminated before hand, +1 from max size. */
            if (to_bin)
            {
                fprintf(output, "%s ", atob(c, output_arr));
                memset(output_arr, 0, BYTE_LENGTH);
            }
            else if (to_caps)
            {
                fprintf(output, "%c", change_letter_case(c));
            }
            else
            {
                fprintf(output,  "%u " ,my_atoi(c));
            }
        }
        else
            fprintf(output, "\n");

        c = getc(stdin);
    }
    return 0;
}