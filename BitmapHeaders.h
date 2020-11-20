#ifndef BITMAPHEADERS_H
#define BITMAPHEADERS_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

typedef unsigned char byte;
typedef unsigned short int word;
typedef unsigned int dword;

typedef struct
{
    byte bfType1;
    byte bfType2;
    dword bfSize;
    word bfReserved1;
    word bfReserved2;
    dword bfOffBits;

} __attribute__((__packed__)) BITMAPFILEHEADER;

typedef struct
{
    dword biSize;
    dword biWidth;
    dword biHeight;
    word biPlanes;
    word biBitCount;
    dword biCompression; //MUST BE 0 TO WORK!!
    dword biSizeImage;
    dword biXPelsPerMeter;
    dword biYPelsPerMeter;
    dword biClrUsed;
    dword biClrImportant;

}__attribute__((__packed__)) BITMAPINFOHEADER;

byte *LoadBitmapFile(char *BMPFileName, BITMAPINFOHEADER *bitmapInfoHeader, BITMAPFILEHEADER *bitmapFileHeader);

void printMETA(BITMAPINFOHEADER *bitmapInfoHeader, BITMAPFILEHEADER *bitmapFileHeader);

#endif // !1