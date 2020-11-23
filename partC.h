#ifndef PARTC_H
#define PARTC_H
#include "BitmapHeaders.h"

void stringToImage(char *imageName, char *strFile);

void imageToString(char *imageName);

int *createFinalBitImage(int height, int width, char *imageData, int biImageSize);

void reverseFinalBitImage(int height, int width, int *bitImage);

#endif