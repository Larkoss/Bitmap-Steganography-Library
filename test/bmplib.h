#ifndef BMPHEADERS_H
#define BMPHEADERS_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

typedef unsigned char byte;
typedef unsigned short int word;
typedef unsigned int dword;

typedef struct
{
    unsigned char riff[4];              // RIFF string
    unsigned int overall_size;          // overall size of file in bytes
    unsigned char wave[4];              // WAVE string
    unsigned char fmt_chunk_marker[4];  // fmt string with trailing null char
    unsigned int length_of_fmt;         // length of the format data
    unsigned int format_type;           // format type. 1-PCM, 3- IEEE float, 6 - 8bit A law, 7 - 8bit mu law
    unsigned int channels;              // no.of channels
    unsigned int sample_rate;           // sampling rate (blocks per second)
    unsigned int byterate;              // SampleRate * NumChannels * BitsPerSample/8
    unsigned int block_align;           // NumChannels * BitsPerSample/8
    unsigned int bits_per_sample;       // bits per sample, 8- 8bits, 16- 16 bits etc
    unsigned char data_chunk_header[4]; // DATA string or FLLR string
    unsigned int data_size;             // NumSamples * NumChannels * BitsPerSample/8 - size of the next chunk that will be read
}__attribute__((__packed__)) WAVHEADER;
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

////////////////////////////////////////////////////////////////////
void grayscale(char *imageName);
////////////////////////////////////////////////////////////////////
void stringToImage(char *imageName, char *strFile);

void imageToString(char *imageName);

int *createFinalBitImage(int height, int width, char *imageData, int biImageSize);

void reverseFinalBitImage(int height, int width, int *bitImage);
////////////////////////////////////////////////////////////////////
void encodeStegano(int nbBits, char *cover, char *secret);
///////////////////////////////////////////////////////////////////
void decodeStegano(int nbBits, char *encryptedImage);

int getBit(char *m, int n);

int * createPermutationFunction(int N, unsigned int systemkey);

void encodeText(char *coverImageName, char *inputTextFileName);

void decodeText(char *encryptedImageName, int msgLength, char *outputFileName);

void redscale(char *imageName);

void greenscale(char *imageName);

void bluescale(char *imageName);

int *createBitImage(int height, int width, char *image, int imageSize);

void encodeAudio(char *pictureName, char *AudioFile);

void decodeAudio(char *BMPFileName);

unsigned char *LoadWavFile(char *WAVfilename, WAVHEADER *header, long *size);



#endif