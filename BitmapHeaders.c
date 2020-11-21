#include "BitmapHeaders.h"
#include "grayscale.h"
#include "Stegano.h"
#include "textInPic.h"

byte *LoadBitmapFile(char *BMPFileName, BITMAPINFOHEADER *bitmapInfoHeader, BITMAPFILEHEADER *bitmapFileHeader)
{
    FILE *filePtr;              //our file pointer
    byte *bitmapImage; //store image data
    int imageIdx = 0;           //image index counter
    byte tempRGB;      //our swap variable

    //open filename in read binary mode
    filePtr = fopen(BMPFileName, "rb");
    if (filePtr == NULL)
        return NULL;

    //read the bitmap file header
    fread(bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);

    //verify that this is a bmp file by check bitmap id
    if (bitmapFileHeader->bfType1 != 0x42 && bitmapFileHeader->bfType2 != 0x4D)
    {
        fclose(filePtr);
        printf("bfType is incorrect\n");
        exit(-9);
    }

    //read the bitmap info header
    fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr); // small edit. forgot to add the closing bracket at sizeof

    //move file point to the begging of bitmap data
    fseek(filePtr, bitmapFileHeader->bfOffBits, SEEK_SET);

    //allocate enough memory for the bitmap image data
    bitmapImage = (unsigned char *)malloc(bitmapInfoHeader->biSizeImage);

    //verify memory allocation
    if (!bitmapImage)
    {
        free(bitmapImage);
        fclose(filePtr);
        return NULL;
    }

    //read in the bitmap image data
    fread(bitmapImage, bitmapInfoHeader->biSizeImage, 1, filePtr);

    //make sure bitmap image data was read
    if (bitmapImage == NULL)
    {
        fclose(filePtr);
        return NULL;
    }

    //swap the r and b values to get RGB (bitmap is BGR)
    for (imageIdx = 0; imageIdx < bitmapInfoHeader->biSizeImage; imageIdx += 3) // fixed semicolon
    {
        tempRGB = bitmapImage[imageIdx];
        bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
        bitmapImage[imageIdx + 2] = tempRGB;
    }

    //close file and return bitmap iamge data
    fclose(filePtr);
    return bitmapImage;
}

void printMETA(BITMAPINFOHEADER *bitmapInfoHeader, BITMAPFILEHEADER *bitmapFileHeader)
{
    printf("BITMAP_FILE_HEADER\n==================");
    printf("\nbfType: %c%c", bitmapFileHeader->bfType1, bitmapFileHeader->bfType2);
    printf("\nbfSize: %d", bitmapFileHeader->bfSize);
    printf("\nbfReserved1: %d", bitmapFileHeader->bfReserved1);
    printf("\nbfReserved2: %d", bitmapFileHeader->bfReserved2);
    printf("\nbfOffBits: %d", bitmapFileHeader->bfOffBits);
    printf("\n");
    printf("\nBITMAP_INFO_HEADER\n==================");
    printf("\nbiSize: %d", bitmapInfoHeader->biSize);
    printf("\nbiWidth: %d", bitmapInfoHeader->biWidth);
    printf("\nbiHeight: %d", bitmapInfoHeader->biHeight);
    printf("\nbiPlanes: %d", bitmapInfoHeader->biPlanes);
    printf("\nbiBitCount: %d", bitmapInfoHeader->biBitCount);
    printf("\nbiCompression: %d", bitmapInfoHeader->biCompression);
    printf("\nbiSizeImage: %d", bitmapInfoHeader->biSizeImage);
    printf("\nbiXPelsPerMeter: %d", bitmapInfoHeader->biXPelsPerMeter);
    printf("\nbiYPelsPerMeter: %d", bitmapInfoHeader->biYPelsPerMeter);
    printf("\nbiClrUsed: %d", bitmapInfoHeader->biClrUsed);
    printf("\nbiClrImportant: %d\n", bitmapInfoHeader->biClrImportant);
}

int main(int args, char *arg[])
{
    // BITMAPINFOHEADER *bitmapInfoHeader = (BITMAPINFOHEADER *)malloc(sizeof(BITMAPINFOHEADER));
    // BITMAPFILEHEADER *bitmapFileHeader = (BITMAPFILEHEADER *)malloc(sizeof(BITMAPFILEHEADER));
    // byte *bitmapImage = LoadBitmapFile(arg[1], bitmapInfoHeader, bitmapFileHeader);
    // printMETA(bitmapInfoHeader, bitmapFileHeader);
    // grayscale(bitmapImage, bitmapInfoHeader, bitmapFileHeader, arg[2]);
    // int nbBits = 4;
    // encodeStegano(nbBits, arg[1], arg[2]);
    //decodeStegano(4,arg[1]);
    //stringToImage(arg[1], arg[2]);

    //printf("\n%d",getBit("clear",2));

    //encodeText(arg[1],arg[2]);


    decodeText(arg[1],arg[2],3);

    
}
