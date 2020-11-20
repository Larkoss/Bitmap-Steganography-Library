#include "textInPic.h"

int getBit(char *m, int n)
{
    if (n < 0 || n > 8 * strlen(m))
    {
        return 0;
    }

    else
    {
        byte M = m[n / 8];

        return (M >> (7 - (n % 8))) % 2;
    }
}

int *createPermutationFunction(int N, unsigned int systemkey)
{
    int permArray[N];

    //Initialize arrayy with simplest permutation f(x) = x
    for (int i = 0; i < N; i++)
    {
        permArray[i] = i;
    }

    //set seed
    srand(systemkey);
    for (int i = 0; i < N; i++)
    {
        int j = rand();
        int k = rand();
        j = j % (N);
        k = k % (N);

        int temp = permArray[j];
        permArray[j] = permArray[k];
        permArray[k] = temp;
    }

    return permArray;
}
