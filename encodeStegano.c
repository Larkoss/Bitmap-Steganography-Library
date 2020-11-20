#include "encodeStegano.h"
#include <string.h>
void encodeStegano(int nbBits, char *cover, char *secret)
{
    //Both files are the same size, so they have the same headers
    //I can declare them once then
    BITMAPINFOHEADER *bitmapInfoHeader = (BITMAPINFOHEADER *)malloc(sizeof(BITMAPINFOHEADER));
    BITMAPFILEHEADER *bitmapFileHeader = (BITMAPFILEHEADER *)malloc(sizeof(BITMAPFILEHEADER));
    //Read both images from files
    byte *coverImage = LoadBitmapFile(cover, bitmapInfoHeader, bitmapFileHeader);
    byte *secretImage = LoadBitmapFile(secret, bitmapInfoHeader, bitmapFileHeader);

    //Create the output name
    char *outputName = (char *)malloc(sizeof(char) * (6 + strlen(cover) + 1));
    outputName = strcat(outputName, "new - ");
    outputName = strcat(outputName, cover);

    //Create the output file
    FILE *outFile;
    outFile = fopen(outputName, "w+");
    if (outFile == NULL)
    {
        //file not created
        printf("Unable to create file\n");
        exit(-9);
    }

    //write the bitmap info header
    fwrite(bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, outFile);

    //write in the bitmap image data
    fwrite(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, outFile);

    //move file point to the begging of bitmap data
    fseek(outFile, bitmapFileHeader->bfOffBits, SEEK_SET);

    byte tempRGB;
    //swap the r and b values to get RGB (bitmap is BGR)
    for (int imageIdx = 0; imageIdx < bitmapInfoHeader->biSizeImage; imageIdx += 3) // fixed semicolon
    {
        tempRGB = coverImage[imageIdx];
        coverImage[imageIdx] = coverImage[imageIdx + 2];
        coverImage[imageIdx + 2] = tempRGB;
        tempRGB = secretImage[imageIdx];
        secretImage[imageIdx] = secretImage[imageIdx + 2];
        secretImage[imageIdx + 2] = tempRGB;
    }

    //Calculate the new byte value and insert it to the output file
    byte newByte, tempByte;
    for (int imageIdx = 0; imageIdx < bitmapInfoHeader->biSizeImage; imageIdx++)
    {
        newByte = coverImage[imageIdx];
        tempByte = secretImage[imageIdx];
        newByte = newByte | ((int)pow(2, nbBits) - 1);
        tempByte = tempByte >> (8 - nbBits);
        tempByte = tempByte << (8 - nbBits);
        tempByte = ~(tempByte);
        tempByte = tempByte >> (8 - nbBits);
        newByte = newByte ^ tempByte;
        putc(newByte, outFile);
    }

    //read in the bitmap image data
    //fwrite(coverImage, bitmapInfoHeader->biSizeImage, 1, outFile);
}