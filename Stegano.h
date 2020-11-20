#ifndef STEGANO_H
#define STEGANO_H
#include "BitmapHeaders.h"
#include <string.h>
void encodeStegano(int nbBits, char *cover, char *secret);

void decodeStegano(int nbBits, char *encryptedImage);

#endif