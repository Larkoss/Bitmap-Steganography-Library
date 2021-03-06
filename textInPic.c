#include "bmplib.h"

int getBit(char *m, int n)
{
    if (n < 0 || n > 8 * strlen(m))
    {
        return 0;
    }

    else
    {
        byte M = m[n / 8];
        return (M >> (7 - (n % 8))) % 2;
    }
}

int *createPermutationFunction(int N, unsigned int systemkey)
{
    int *permArray = (int *)malloc(N * sizeof(int));

    //Initialize arrayy with simplest permutation f(x) = x
    for (int i = 0; i < N; i++)
    {
        permArray[i] = i;
    }

    //set seed
    srand(systemkey);
    for (int i = 0; i < N; i++)
    {
        int j = rand();
        int k = rand();
        j = j % (N);
        k = k % (N);

        int temp = permArray[j];
        permArray[j] = permArray[k];
        permArray[k] = temp;
    }

    return permArray;
}

void encodeText(char *coverImageName, char *inputTextFileName)
{
    BITMAPFILEHEADER *bitmapFileHeader = (BITMAPFILEHEADER *)malloc(sizeof(BITMAPFILEHEADER));
    BITMAPINFOHEADER *bitmapInfoHeader = (BITMAPINFOHEADER *)malloc(sizeof(BITMAPINFOHEADER));
    byte *BMPDataArray = LoadBitmapFile(coverImageName, bitmapInfoHeader, bitmapFileHeader);

    if (bitmapInfoHeader->biCompression != 0)
    {
        printf("Image is compressed!\n");
        free(bitmapInfoHeader);
        free(bitmapFileHeader);
        free(BMPDataArray);
        exit(-10);
    }
    if (bitmapFileHeader->bfType1 != 0x42 && bitmapFileHeader->bfType2 != 0x4D)
    {
        printf("bfType is incorrect\n");
        free(bitmapInfoHeader);
        free(bitmapFileHeader);
        free(BMPDataArray);
        exit(-10);
    }

    byte tempRGB;

    for (int i = 0; i < bitmapInfoHeader->biSizeImage; i += 3) // fixed semicolon
    {
        tempRGB = BMPDataArray[i];
        BMPDataArray[i] = BMPDataArray[i + 2];
        BMPDataArray[i + 2] = tempRGB;
    }

    char *name = (char *)malloc(5 + strlen(coverImageName));
    name[0] = '\0';
    strcat(name, "new-");
    strcat(name, coverImageName);

    FILE *outputImage = fopen(name, "w");
    FILE *secretMessage = fopen(inputTextFileName, "r");

    //Find the length of the file
    fseek(secretMessage, 0, SEEK_END);
    long sizeFile = ftell(secretMessage);
    fseek(secretMessage, 0, SEEK_SET);

    //read the file
    char *message = (char *)malloc((sizeFile + 1) * sizeof(char));
    char temp[1024];
    while (fgets(temp, 1024, secretMessage) != NULL)
    {
        strcat(message, temp);
    }

    //Write bitmapFileHeader,bitmapInfoHeader to the new immage
    fwrite(bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, outputImage);
    fwrite(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, outputImage);
    fseek(outputImage, bitmapFileHeader->bfOffBits, SEEK_SET);

    int *permutation = createPermutationFunction(bitmapInfoHeader->biSizeImage, 78);

    for (int i = 0; i < 1 + 8 * strlen(message); i++)
    {
        int b = getBit(message, i);
        int o = permutation[i];
        BMPDataArray[o] = BMPDataArray[o] >> 1;
        BMPDataArray[o] = BMPDataArray[o] << 1;
        BMPDataArray[o] = BMPDataArray[o] | b;
    }

    for (int i = 0; i < bitmapInfoHeader->biSizeImage; i++)
    {
        fputc(BMPDataArray[i], outputImage);
    }

    free(bitmapFileHeader);
    free(bitmapInfoHeader);
    free(message);
    free(permutation);
    free(BMPDataArray);
    free(name);
    fclose(outputImage);
    fclose(secretMessage);
}

void decodeText(char *encryptedImageName, int msgLength, char *outputFileName)
{
    BITMAPFILEHEADER *bitmapFileHeader = (BITMAPFILEHEADER *)malloc(sizeof(BITMAPFILEHEADER));
    BITMAPINFOHEADER *bitmapInfoHeader = (BITMAPINFOHEADER *)malloc(sizeof(BITMAPINFOHEADER));
    byte *BMPDataArray = LoadBitmapFile(encryptedImageName, bitmapInfoHeader, bitmapFileHeader);

    if (bitmapInfoHeader->biCompression != 0)
    {
        printf("Image is compressed!\n");
        free(bitmapInfoHeader);
        free(bitmapFileHeader);
        free(BMPDataArray);
        exit(-10);
    }
    if (bitmapFileHeader->bfType1 != 0x42 && bitmapFileHeader->bfType2 != 0x4D)
    {
        printf("bfType is incorrect\n");
        free(bitmapInfoHeader);
        free(bitmapFileHeader);
        free(BMPDataArray);
        exit(-10);
    }

    byte tempRGB;

    for (int i = 0; i < bitmapInfoHeader->biSizeImage; i += 3) // fixed semicolon
    {
        tempRGB = BMPDataArray[i];
        BMPDataArray[i] = BMPDataArray[i + 2];
        BMPDataArray[i + 2] = tempRGB;
    }

    FILE *outputTXT = fopen(outputFileName, "w");

    int *permutation = createPermutationFunction(bitmapInfoHeader->biSizeImage, 78);

    char byteWriter[msgLength + 1];
    for (int i = 0; i < msgLength + 1; i++)
    {
        byteWriter[i] = 0;
    }

    for (int i = 0; i < 8 * msgLength + 1; i++)
    {
        int o = permutation[i];
        int B = BMPDataArray[o];

        B = B % 2;

        byteWriter[i / 8] = byteWriter[i / 8] + pow(2, (7 - (i % 8))) * B;
    }

    for (int i = 0; i < msgLength; i++)
    {
        putc(byteWriter[i], outputTXT);
    }
    free(bitmapFileHeader);
    free(bitmapInfoHeader);
    free(permutation);
    free(BMPDataArray);
    fclose(outputTXT);
}

#ifdef DEBUGINPIC
int main()
{

    encodeText("IMG_6865.bmp", "out.txt");
}

#endif // DEBUG