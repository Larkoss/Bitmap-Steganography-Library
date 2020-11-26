#include "bmplib.h"

int main(int args, char *argv[])
{

    printf("bmpSteganography Copyright (C) 2020  Stylianos Sofokleous & Konstantinos Larkou\nThis program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.\nThis is free software, and you are welcome to redistribute it\nunder certain conditions\n");

    if (args < 3)
    {
        printf("Not enough arguments!\n");
        exit(-10);
    }

    if (strcmp(argv[1], "-list") == 0)
    {
        for (int i = 2; i < args; i++)
        {
            BITMAPINFOHEADER *bitmapInfoHeader = (BITMAPINFOHEADER *)malloc(sizeof(BITMAPINFOHEADER));
            BITMAPFILEHEADER *bitmapFileHeader = (BITMAPFILEHEADER *)malloc(sizeof(BITMAPFILEHEADER));
            byte *bitmapImage = LoadBitmapFile(argv[i], bitmapInfoHeader, bitmapFileHeader);

            //verify that this is a bmp file by check bitmap id
            if (bitmapFileHeader->bfType1 != 0x42 && bitmapFileHeader->bfType2 != 0x4D)
            {
                printf("bfType is incorrect\n");
                continue;
            }

            if (bitmapInfoHeader->biCompression != 0)
            {
                printf("Image is compressed!\n");
                continue;
            }

            printMETA(bitmapInfoHeader,bitmapFileHeader);
            free(bitmapInfoHeader);
            free(bitmapFileHeader);
            free(bitmapImage);
        }
    }

    else if (strcmp(argv[1], "-grayscale") == 0)
    {
        for (int i = 2; i < args; i++)
        {
            BITMAPINFOHEADER *bitmapInfoHeader = (BITMAPINFOHEADER *)malloc(sizeof(BITMAPINFOHEADER));
            BITMAPFILEHEADER *bitmapFileHeader = (BITMAPFILEHEADER *)malloc(sizeof(BITMAPFILEHEADER));
            byte *bitmapImage = LoadBitmapFile(argv[i], bitmapInfoHeader, bitmapFileHeader);

            //verify that this is a bmp file by check bitmap id
            if (bitmapFileHeader->bfType1 != 0x42 && bitmapFileHeader->bfType2 != 0x4D)
            {
                printf("bfType is incorrect\n");
                continue;
            }

            if (bitmapInfoHeader->biCompression != 0)
            {
                printf("Image is compressed!\n");
                continue;
            }
            free(bitmapInfoHeader);
            free(bitmapFileHeader);
            free(bitmapImage);
            grayscale(argv[i]);
            
        }
    }

    else if(strcmp(argv[1], "-encodeStegano") == 0){
        encodeStegano(atoi(argv[2]),argv[3],argv[4]);
    }

     
}
