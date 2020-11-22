#ifndef PARTC_H
#define PARTC_H
#include "BitmapHeaders.h"

void stringToImage(char *imageName, char *strFile);

void imageToString(char *strFile);

int *createFinalBitImage(int height, int width, char *imageData, int biImageSize);

#endif