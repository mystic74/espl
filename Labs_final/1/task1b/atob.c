

/*
* @param c          -   ascii character of some kind
* @param out_arr[8] -   a binary representation of the c character, either int or char wise.
*                       depends on if TO_INT is defined.
*/
char* atob(char c, char out_arr[8])
{
    int tempnum = 0;
    int index = 0;

    for (index = 0; index < 8; index++)
    {
        tempnum = c >> index;
        #ifdef TO_INT
            out_arr[index] = (tempnum & 1);
        #else
            if ((tempnum & 1) == 1)
                out_arr[index] = '1';
            else
                out_arr[index] = '0';
        #endif
        
    }
    return out_arr;
}