#include"partC.h"

void stringToImage(char *imageName, char *strFile)
{
    BITMAPINFOHEADER *bitmapInfoHeader = (BITMAPINFOHEADER *)malloc(sizeof(BITMAPINFOHEADER));
    BITMAPFILEHEADER *bitmapFileHeader = (BITMAPFILEHEADER *)malloc(sizeof(BITMAPFILEHEADER));
    byte *imageData= LoadBitmapFile(imageName, bitmapInfoHeader, bitmapFileHeader);
    printMETA(bitmapInfoHeader, bitmapFileHeader);
    //Create the output name
    char *outputName = (char *)malloc(sizeof(char) * (6 + strlen(imageName) + 1));
    outputName = strcat(outputName, "new - ");
    outputName = strcat(outputName, imageName);

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

    //allocate enough memory for the bitmap image data
    //byte *newImage = (byte *)malloc(bitmapInfoHeader->biSizeImage);

    // int width = bitmapInfoHeader->biWidth, height = bitmapInfoHeader->biHeight;
    // printf("height = %d, width = %d\n", height, width);
    // int count = 0;
    // for (int j = width; j <= width * height; j*=2){
    //     for (int i = 0; i < height; i++){
    //         newImage[count++] = imageData[j - i];
    //         printf("%c ", count);
    //     }
    //     printf("\n");
    // }
    
    //write in the bitmap image data
    //fwrite(outputName, bitmapInfoHeader->biSizeImage, 1, outFile);

}

void imamgeToString(char *strFile)
{

}