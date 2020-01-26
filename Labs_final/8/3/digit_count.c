#include <stdio.h>

int count_dig(char* stringy)
{
    int digit = 0;
    int i = 0;
    while(stringy[i]!='\0')
    {
        if(stringy[i]>='0' && stringy[i]<='9')
        {
            digit++;
        }
        i++;
    }
    return digit;
}

void main()
{
    char str[1000];
    int alp, digit, splch, i;
    alp = digit = splch = i = 0;


       printf("\n\nCount total number of alphabets, digits and special characters :\n");
       printf("--------------------------------------------------------------------\n"); 	
       printf("Input the string : ");
       fgets(str, sizeof str, stdin);	

     /* Checks each character of string*/
    digit = count_dig(str);
    while(str[i]!='\0')
    {
        if((str[i]>='a' && str[i]<='z') || (str[i]>='A' && str[i]<='Z'))
        {
            alp++;
        }
        else
        {
            splch++;
        }

        i++;
    }

    printf("Number of Alphabets in the string is : %d\n", alp);
    printf("Number of Digits in the string is : %d\n", digit);
    printf("Number of Special characters in the string is : %d\n\n", splch);
}