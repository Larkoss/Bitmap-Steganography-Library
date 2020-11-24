#include "partC.h"

//Function that reads the text from a file
//and return the number of characters read
char *readTXT(char *fileName, int *textSize)
{
    FILE *file = fopen(fileName, "r");
    char *code;
    size_t n = 0;
    int c;

    if (file == NULL)
        return NULL; //could not open file
    fseek(file, 0, SEEK_END);
    long f_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    code = malloc(f_size);

    while ((c = fgetc(file)) != EOF)
    {
        code[n++] = (char)c;
    }

    fclose(file);
    code[n] = '\0';
    *textSize = n;
    return code;
}

//Function that uses function from byteManipulation.c
//in order to read text, create array of bits and set the 
//pixels of the image accordingly
void stringToImage(char *imageName, char *strFile)
{
    //Read image to calculate new image's Info Header & File Header
    BITMAPINFOHEADER *bitmapInfoHeader = (BITMAPINFOHEADER *)malloc(sizeof(BITMAPINFOHEADER));
    BITMAPFILEHEADER *bitmapFileHeader = (BITMAPFILEHEADER *)malloc(sizeof(BITMAPFILEHEADER));
    byte *imageData = LoadBitmapFile(imageName, bitmapInfoHeader, bitmapFileHeader);
    //printMETA(bitmapInfoHeader, bitmapFileHeader);

    //Read all character from the file
    int textSize;
    char *text = readTXT(strFile, &textSize);

    //Create the output name
    char *outputName = (char *)malloc(sizeof(char) * (strlen(imageName) + 5));
    char *dummy = outputName;
    *dummy = '\0';
    outputName = strcat(outputName, "new-");
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
    free(outputName);

    //write the bitmap info header
    fwrite(bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, outFile);

    //write in the bitmap image data
    fwrite(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, outFile);

    //move file point to the begging of bitmap data
    fseek(outFile, bitmapFileHeader->bfOffBits, SEEK_SET);

    //printf("size of file = %d\n", textSize);
    //printf("%c %c\n", text[0], text[1]);
    int *bitData = createFinalBitImage(bitmapInfoHeader->biHeight, bitmapInfoHeader->biWidth, text, textSize);
    int count = 0;
    //printf("height = %d, width = %d\n", bitmapInfoHeader->biHeight, bitmapInfoHeader->biWidth);

    for (int i = 0; i < bitmapInfoHeader->biSizeImage; i += 3) // fixed semicolon
        if (bitData[count++] == 0)
        {
            fputc(0, outFile);
            fputc(0, outFile);
            fputc(0, outFile);
        }
        else
        {
            fputc(128, outFile);
            fputc(128, outFile);
            fputc(128, outFile);
        }
    fclose(outFile);
    free(bitData);
    free(bitmapInfoHeader);
    free(bitmapFileHeader);
    free(imageData);
    free(text);
}

//Reverse engineer the above function in order to read pixels from image
//find the array of bits it represents and turn it into array of characters
//which is the text that is added to output file
void imageToString(char *imageName)
{
    //Read image to calculate new image's Info Header & File Header
    BITMAPINFOHEADER *bitmapInfoHeader = (BITMAPINFOHEADER *)malloc(sizeof(BITMAPINFOHEADER));
    BITMAPFILEHEADER *bitmapFileHeader = (BITMAPFILEHEADER *)malloc(sizeof(BITMAPFILEHEADER));
    byte *imageData = LoadBitmapFile(imageName, bitmapInfoHeader, bitmapFileHeader);

    //Create the output file
    FILE *outFile;
    outFile = fopen("outputText.txt", "w+");
    if (outFile == NULL)
    {
        //file not created
        printf("Unable to create file\n");
        exit(-9);
    }

    int height = bitmapInfoHeader->biHeight, width = bitmapInfoHeader->biWidth;
    int *bitImage = (int *)malloc(sizeof(int) * width * height * 8);
    int count = 0;
    for (int i = 0; i < bitmapInfoHeader->biSizeImage; i += 3) 
    {
        if(imageData[i] == 0)
            bitImage[count++] = 0;
        else
            bitImage[count++] = 1;
    }

    reverseFinalBitImage(height, width, bitImage);

    char tempChar;
    for(int i = 0; i < count; i+=8)
    {
        tempChar = 0;
        for(int j = 0; j < 8; j++)
            if(bitImage[i + j] == 1)
                tempChar += pow(2, 7 - j);
        fputc(tempChar, outFile);
    }
    free(bitImage);
    free(bitmapInfoHeader);
    free(bitmapFileHeader);
    free(imageData);
    fclose(outFile);
}