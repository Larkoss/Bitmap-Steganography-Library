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
    dword bfSize; //Specifies the size of the file (including padding) in bytes
    word bfReserved1;
    word bfReserved2;
    dword bfOffBits;//Specifies the offset from the beginning of the file to the bitmap data.

} __attribute__((__packed__)) BITMAPFILEHEADER;

typedef struct
{
    dword biSize;//Specifies the size of the BITMAPINFOHEADER structure, in bytes.
    dword biWidth;//Specifies the width of the image, in pixels.
    dword biHeight;//Specifies the height of the image, in pixels.
    word biPlanes;
    word biBitCount;//Specifies the number of bits per pixel.
    dword biCompression; //MUST BE 0 TO WORK!!
    dword biSizeImage;//Specifies the size of the image data, in bytes
    dword biXPelsPerMeter;
    dword biYPelsPerMeter;
    dword biClrUsed;
    dword biClrImportant;

}__attribute__((__packed__)) BITMAPINFOHEADER;

byte *LoadBitmapFile(char *BMPFileName, BITMAPINFOHEADER *bitmapInfoHeader, BITMAPFILEHEADER *bitmapFileHeader);

void printMETA(BITMAPINFOHEADER *bitmapInfoHeader, BITMAPFILEHEADER *bitmapFileHeader);

#endif // !1