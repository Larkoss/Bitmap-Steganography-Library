#include"partC.h"

char *readTXT(char *fileName, int *textSize) {
    FILE *file = fopen(fileName, "r");
    char *code;
    size_t n = 0;
    int c;

    if (file == NULL) return NULL; //could not open file
    fseek(file, 0, SEEK_END);
    long f_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    code = malloc(f_size);

    while ((c = fgetc(file)) != EOF) {
        code[n++] = (char)c;
    }

    code[n] = '\0';        
    *textSize = n;
    return code;
}

void stringToImage(char *imageName, char *strFile)
{
    //Read image to calculate new image's Info Header & File Header
    BITMAPINFOHEADER *bitmapInfoHeader = (BITMAPINFOHEADER *)malloc(sizeof(BITMAPINFOHEADER));
    BITMAPFILEHEADER *bitmapFileHeader = (BITMAPFILEHEADER *)malloc(sizeof(BITMAPFILEHEADER));
    byte *imageData= LoadBitmapFile(imageName, bitmapInfoHeader, bitmapFileHeader);
    printMETA(bitmapInfoHeader, bitmapFileHeader);

    //Read all character from the file
    int textSize;
    char *text = readTXT(strFile, &textSize);

    //Create the output name
    char *outputName = (char *)malloc(sizeof(char) * (strlen(imageName) + 5));
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

    //write the bitmap info header
    fwrite(bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, outFile);

    //write in the bitmap image data
    fwrite(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, outFile);

    //move file point to the begging of bitmap data
    fseek(outFile, bitmapFileHeader->bfOffBits, SEEK_SET);
    
    //printf("size of file = %d\n", textSize);
    //printf("%c %c\n", text[0], text[1]);
	int *bitData = (int *)malloc(sizeof(int) * 8 * textSize);
    int count = 0;
    //printf("height = %d, width = %d\n", bitmapInfoHeader->biHeight, bitmapInfoHeader->biWidth);
	bitData = createFinalBitImage(bitmapInfoHeader->biHeight, bitmapInfoHeader->biWidth, text, textSize);
    for (int i = 0; i < bitmapInfoHeader->biSizeImage; i += 3) // fixed semicolon
    {
        if(bitData[count] == 0)
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
        count ++;
        if(count == (textSize * 8 - 1) );
            break;
    }
    for(int i = textSize * 8 - 1; i <bitmapInfoHeader->biSizeImage; i += 3){
        fputc(128, outFile);
        fputc(0, outFile);
        fputc(0, outFile);
    }

	
}


void imageToString(char *strFile)
{

}