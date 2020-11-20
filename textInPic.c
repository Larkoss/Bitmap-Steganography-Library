#include "textInPic.h"

int getBit(char *m, int n)
{
    if (n < 0 || n > 8 * strlen(m))
    {
        return 0;
    }

    else
    {
        byte M = m[n/8];

        return (M >> (7-(n % 8)))%2;


    }
    
}