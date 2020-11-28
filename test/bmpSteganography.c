#include "bmplib.h"

int main(int args, char *argv[])
{

    printf("bmpSteganography Copyright (C) 2020  Stylianos Sofokleous & Konstantinos Larkou\nThis program comes with ABSOLUTELY NO WARRANTY.\nThis is free software, and you are welcome to redistribute it\nunder certain conditions\n");

    if (args < 3)
    {
        printf("Not enough arguments!\n");
        exit(-10);
    }

    //OPERATION 1: -list
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

            printMETA(bitmapInfoHeader, bitmapFileHeader);
            free(bitmapInfoHeader);
            free(bitmapFileHeader);
            free(bitmapImage);
        }
    }

    //OPERATION 2: -grayscale
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

    //OPERATION 3: -encodeStegano
    else if (strcmp(argv[1], "-encodeStegano") == 0)
    {
        encodeStegano(atoi(argv[2]), argv[3], argv[4]);
    }

    //OPERATION 4: -decodeStegano
    else if (strcmp(argv[1], "-decodeStegano") == 0)
    {
        decodeStegano(atoi(argv[2]), argv[3]);
    }

    //OPERATION 5: -encodeText
    else if (strcmp(argv[1], "-encodeText") == 0)
    {
        encodeText(argv[2], argv[3]);
    }

    //OPERATION 6: -decodeText
    else if (strcmp(argv[1], "-decodeText") == 0)
    {
        decodeText(argv[2], atoi(argv[3]), argv[4]);
    }

    //OPERATION 7: -stringToImage
    else if (strcmp(argv[1], "-stringToImage") == 0)
    {
        stringToImage(argv[2], argv[3]);
    }

    //OPERATION 8: -imageToString
    else if (strcmp(argv[1], "-imageToString") == 0)
    {
        imageToString(argv[2]);
    }
    //OPERATION 9: -redscale
    else if (strcmp(argv[1], "-greenscale") == 0)
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
            greenscale(argv[i]);
        }
    }
     //OPERATION 10: -redscale
    else if (strcmp(argv[1], "-redscale") == 0)
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
            redscale(argv[i]);
        }
    }
    //OPERATION 11: -bluescale
    else if (strcmp(argv[1], "-bluescale") == 0)
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
            bluescale(argv[i]);
        }
    }

    //Operation 12
    else if(strcmp(argv[1], "-encodeAudio") == 0){
        encodeAudio(argv[2],argv[3]);
    }

    //Operation 13
    else if (strcmp(argv[1], "-decodeAudio") == 0)
    {
        decodeAudio(argv[2]);
    }

    else
    {
        printf("Error! Operation not found\n");
    }

    
}
