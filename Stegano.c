#include "bmplib.h"

void encodeStegano(int nbBits, char *cover, char *secret)
{
    BITMAPINFOHEADER *coverInfoHeader = (BITMAPINFOHEADER *)malloc(sizeof(BITMAPINFOHEADER));
    BITMAPFILEHEADER *coverFileHeader = (BITMAPFILEHEADER *)malloc(sizeof(BITMAPFILEHEADER));
    byte *coverImage = LoadBitmapFile(cover, coverInfoHeader, coverFileHeader);

    BITMAPINFOHEADER *secretInfoHeader = (BITMAPINFOHEADER *)malloc(sizeof(BITMAPINFOHEADER));
    BITMAPFILEHEADER *secretFileHeader = (BITMAPFILEHEADER *)malloc(sizeof(BITMAPFILEHEADER));
    //Read both images from files

    byte *secretImage = LoadBitmapFile(secret, secretInfoHeader, secretFileHeader);
    if (secretInfoHeader->biHeight != coverInfoHeader->biHeight || secretInfoHeader->biWidth != coverInfoHeader->biWidth)
    {
        printf("Pictures not the same size!\n");

        free(secretInfoHeader);
        free(secretFileHeader);
        free(coverFileHeader);
        free(coverInfoHeader);
        free(coverImage);
        free(secretImage);
        exit(-10);
    }
    if (coverFileHeader->bfType1 != 0x42 && coverFileHeader->bfType2 != 0x4D)
    {
        printf("bfType is incorrect\n");
        free(secretInfoHeader);
        free(secretFileHeader);
        free(coverFileHeader);
        free(coverInfoHeader);
        free(coverImage);
        free(secretImage);
        exit(-10);
    }

    if (coverInfoHeader->biCompression != 0)
    {
        printf("Image is compressed!\n");
        free(secretInfoHeader);
        free(secretFileHeader);
        free(coverFileHeader);
        free(coverInfoHeader);
        free(coverImage);
        free(secretImage);
        exit(-10);
    }
    if (secretFileHeader->bfType1 != 0x42 && secretFileHeader->bfType2 != 0x4D)
    {
        printf("bfType is incorrect\n");
        free(secretInfoHeader);
        free(secretFileHeader);
        free(coverFileHeader);
        free(coverInfoHeader);
        free(coverImage);
        free(secretImage);
        exit(-10);
    }

    if (secretInfoHeader->biCompression != 0)
    {
        printf("Image is compressed!\n");
        free(secretInfoHeader);
        free(secretFileHeader);
        free(coverFileHeader);
        free(coverInfoHeader);
        free(coverImage);
        free(secretImage);
        exit(-10);
    }
    //Create the output name
    char *outputName = (char *)malloc((5 + strlen(cover)));
    outputName[0] = '\0';
    outputName = strcat(outputName, "new-");
    outputName = strcat(outputName, cover);

    //Create the output file
    FILE *outFile;
    outFile = fopen(outputName, "w+");
    if (outFile == NULL)
    {
        //file not created
        printf("Unable to create file\n");
        fclose(outFile);
        free(secretInfoHeader);
        free(secretFileHeader);
        free(coverFileHeader);
        free(coverInfoHeader);
        free(outputName);
        free(coverImage);
        free(secretImage);
        exit(-9);
    }

    //write the bitmap info header
    fwrite(secretFileHeader, sizeof(BITMAPFILEHEADER), 1, outFile);

    //write in the bitmap image data
    fwrite(secretInfoHeader, sizeof(BITMAPINFOHEADER), 1, outFile);

    //move file point to the begging of bitmap data
    fseek(outFile, secretFileHeader->bfOffBits, SEEK_SET);

    byte tempRGB;
    //swap the r and b values to get RGB (bitmap is BGR)
    for (int imageIdx = 0; imageIdx < secretInfoHeader->biSizeImage; imageIdx += 3) // fixed semicolon
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
    for (int imageIdx = 0; imageIdx < secretInfoHeader->biSizeImage; imageIdx++)
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

    fclose(outFile);
    free(secretInfoHeader);
    free(secretFileHeader);
    free(coverFileHeader);
    free(coverInfoHeader);
    free(outputName);
    free(coverImage);
    free(secretImage);
}

void decodeStegano(int nbBits, char *encryptedImage)
{

    BITMAPINFOHEADER *bitmapInfoHeader = (BITMAPINFOHEADER *)malloc(sizeof(BITMAPINFOHEADER));
    BITMAPFILEHEADER *bitmapFileHeader = (BITMAPFILEHEADER *)malloc(sizeof(BITMAPFILEHEADER));

    byte *BMPEncoded = LoadBitmapFile(encryptedImage, bitmapInfoHeader, bitmapFileHeader);

    byte tempRGB;
    for (int i = 0; i < bitmapInfoHeader->biSizeImage; i += 3)
    {
        tempRGB = BMPEncoded[i];
        BMPEncoded[i] = BMPEncoded[i + 2];
        BMPEncoded[i + 2] = tempRGB;
    }

    char *name = (char *)malloc(5 + strlen(encryptedImage));
    name[0] = '\0';
    strcat(name, "new-");
    strcat(name, encryptedImage);

    FILE *outputBMP = fopen(name, "w+");
    if (outputBMP == NULL)
    {
        printf("Unable to create file\n");
        exit(-9);
    }

    fwrite(bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, outputBMP);
    fwrite(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, outputBMP);

    fseek(outputBMP, bitmapFileHeader->bfOffBits, SEEK_SET);

    byte newByte;
    for (int i = 0; i < bitmapInfoHeader->biSizeImage; i++)
    {
        newByte = BMPEncoded[i];
        newByte = newByte % (int)pow(2, nbBits);
        newByte = newByte << (8 - nbBits);
        putc(newByte, outputBMP);
    }

    fclose(outputBMP);
    free(bitmapInfoHeader);
    free(bitmapFileHeader);
    free(name);
    free(BMPEncoded);
}

#ifdef DEBUGSTEGANO

int main()
{

    encodeStegano(4, "IMG_6865.bmp", "IMG_6875.bmp");
    decodeStegano(4, "new-IMG_6865.bmp");
}

#endif // DEBUG