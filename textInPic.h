#ifndef TEXTINPIC_H
#define TEXTINPIC_H

#include "BitmapHeaders.h"

int getBit(char *m, int n);

int * createPermutationFunction(int N, unsigned int systemkey);

void encodeText(char *coverImageName, char *inputTextFileName, int syskey);

#endif // !1