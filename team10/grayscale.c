#include "bmplib.h"
void grayscale(char *imageName)
{
    BITMAPINFOHEADER *bitmapInfoHeader = (BITMAPINFOHEADER *)malloc(sizeof(BITMAPINFOHEADER));
    BITMAPFILEHEADER *bitmapFileHeader = (BITMAPFILEHEADER *)malloc(sizeof(BITMAPFILEHEADER));
    byte *bitmapImage = LoadBitmapFile(imageName, bitmapInfoHeader, bitmapFileHeader);
    
    //Create the output name
    char *outputName = (char *)malloc(sizeof(char) * (strlen(imageName) + 5));
    char *dummy = outputName;
    *dummy = '\0';
    outputName = strcat(outputName, "new-");
    outputName = strcat(outputName, imageName);

    FILE *outFile; //destination file
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

    //luminance of grey pixel
    byte lum = 0;                                                                    
    for (int imageIdx = 0; imageIdx < bitmapInfoHeader->biSizeImage; imageIdx += 3) // fixed semicolon
    {
        //calculate luminance
        lum = round(0.299 * (float)bitmapImage[imageIdx] + 0.587 * (float)bitmapImage[imageIdx + 1] + 0.114 * (float)bitmapImage[imageIdx + 2]);
        //set pixel's RGB to be equal to luminance (R, G, B) = (lum, lum, lum)
        fputc(lum, outFile);
        fputc(lum, outFile);
        fputc(lum, outFile);
    }
    fclose(outFile);
    free(bitmapInfoHeader);
    free(bitmapFileHeader);
    free(outputName);
    free(bitmapImage);
}

#ifdef DEBUGGRAY
int main(){

    grayscale("IMG_6865.bmp");

}
#endif // DEBUG

