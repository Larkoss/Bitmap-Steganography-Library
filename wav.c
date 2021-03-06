#include "bmplib.h"

void encodeAudio(char *pictureName, char *AudioFile)
{
    BITMAPINFOHEADER *bitmapInfoHeader = (BITMAPINFOHEADER *)malloc(sizeof(BITMAPINFOHEADER));
    BITMAPFILEHEADER *bitmapFileHeader = (BITMAPFILEHEADER *)malloc(sizeof(BITMAPFILEHEADER));
    byte *bitmapImage = LoadBitmapFile(pictureName, bitmapInfoHeader, bitmapFileHeader);

    WAVHEADER *wavHeader = (WAVHEADER *)malloc(sizeof(WAVHEADER));
    long sizeOfFIle = 0;
    unsigned char *wavData = LoadWavFile(AudioFile, wavHeader, &sizeOfFIle);

    FILE *newAudioImage = fopen("NewAudio.bmp", "w");
    //write the bitmap info header
    fwrite(bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, newAudioImage);

    //write in the bitmap image data
    fwrite(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, newAudioImage);

    //move file point to the begging of bitmap data
    fseek(newAudioImage, bitmapFileHeader->bfOffBits, SEEK_SET);
    fwrite(wavHeader, sizeof(WAVHEADER), 1, newAudioImage);
    fseek(newAudioImage, bitmapFileHeader->bfOffBits + 44, SEEK_SET);
    int *newImage = createBitImage(bitmapInfoHeader->biHeight, bitmapInfoHeader->biWidth, wavData, sizeOfFIle - 44);

    int count = 0;

    for (int i = 0; i < bitmapInfoHeader->biSizeImage; i += 3)
    { // fixed semicolon
        if (newImage[count++] == 0)
        {
            fputc(0, newAudioImage);
            fputc(0, newAudioImage);
            fputc(0, newAudioImage);
        }
        else
        {
            fputc(128, newAudioImage);
            fputc(128, newAudioImage);
            fputc(128, newAudioImage);
        }
    }

    free(wavHeader);
    free(bitmapInfoHeader);
    free(bitmapFileHeader);
    free(bitmapImage);
    free(wavData);
    free(newImage);
    fclose(newAudioImage);
}

void decodeAudio(char *BMPFileName)
{
    BITMAPINFOHEADER *bitmapInfoHeader = (BITMAPINFOHEADER *)malloc(sizeof(BITMAPINFOHEADER));
    BITMAPFILEHEADER *bitmapFileHeader = (BITMAPFILEHEADER *)malloc(sizeof(BITMAPFILEHEADER));
    byte *bytes = LoadBitmapFile(BMPFileName, bitmapInfoHeader, bitmapFileHeader);

    FILE *WAVOut = fopen("Decrypted.wav", "w");

    byte tempRGB;
    for (int i = 0; i < bitmapInfoHeader->biSizeImage; i += 3)
    {
        tempRGB = bytes[i];
        bytes[i] = bytes[i + 2];
        bytes[i + 2] = tempRGB;
    }

    for (int i = 0; i < 44; i++)
    {
        fputc(bytes[i], WAVOut);
    }

    /**
     * @brief Read 3 bytes and creates an array of bits
     * 
     */
    int height = bitmapInfoHeader->biHeight, width = bitmapInfoHeader->biWidth;
    int *bits = (int *)malloc(sizeof(int) * width * height * 8);
    int count = 0;
    for (int i = 44; i < bitmapInfoHeader->biSizeImage; i += 3)
    {
        if (bytes[i] == 0)
            bits[count++] = 0;
        else
            bits[count++] = 1;
    }

    char tempChar = 0;
    for (int i = 0; i < count; i += 8)
    {
        tempChar = 0;
        for (int j = 0; j < 8; j++)
            if (bits[i + j] == 1)
                tempChar += pow(2, 7 - j);
        fputc(tempChar, WAVOut);
    }

    fclose(WAVOut);
    free(bitmapInfoHeader);
    free(bitmapFileHeader);
    free(bytes);
    free(bits);
}

/**
 * @brief This method loads the header of WAV to a compatible struct and creates a data table
 *        That contains the bytes of the audio file
 * 
 * @param WAVfilename The name of the WAV file
 * @param header A pointer to the WAV header struct
 * @param size To return the size of the wav file
 * @return unsigned char* The array with the bytes
 */
unsigned char *LoadWavFile(char *WAVfilename, WAVHEADER *header, long *size)
{
    unsigned char *WAVdata;
    FILE *WAVFile = fopen(WAVfilename, "rb");

    fread(header, sizeof(WAVHEADER), 1, WAVFile);

    fseek(WAVFile, 44, SEEK_SET);

    fseek(WAVFile, 0, SEEK_END);
    long sizeFile = ftell(WAVFile);
    fseek(WAVFile, 44, SEEK_SET);

    WAVdata = (unsigned char *)malloc(sizeFile);
    fread(WAVdata, sizeFile - 44, 1, WAVFile);

    *size = sizeFile;
    fclose(WAVFile);
    return (WAVdata);

    
}

#ifdef DEBUGAUDIO
int main()
{
    encodeAudio("IMG_6865.bmp", "Click2-Sebastian-759472264.wav");
    decodeAudio("NewAudio.bmp");
}
#endif // DEBUG
