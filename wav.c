#include "wav.h"

void encodeAudio(char *pictureName, char *AudioFile)
{

    BITMAPINFOHEADER *bitmapInfoHeader = (BITMAPINFOHEADER *)malloc(sizeof(BITMAPINFOHEADER));
    BITMAPFILEHEADER *bitmapFileHeader = (BITMAPFILEHEADER *)malloc(sizeof(BITMAPFILEHEADER));
    byte *bitmapImage = LoadBitmapFile(pictureName, bitmapInfoHeader, bitmapFileHeader);

    WAVHEADER *wavHeader = (WAVHEADER *)malloc(sizeof(WAVHEADER));
    long sizeOfFIle = 0;
    unsigned char *wavData = LoadWavFile(AudioFile, wavHeader, &sizeOfFIle);


    FILE *newAudioImage = fopen("NewAudio.bmp","w");
    //write the bitmap info header
    fwrite(bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, newAudioImage);

    //write in the bitmap image data
    fwrite(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, newAudioImage);
    

    //move file point to the begging of bitmap data
    fseek(newAudioImage, bitmapFileHeader->bfOffBits, SEEK_SET);
    fwrite(wavHeader,sizeof(WAVHEADER),1,newAudioImage);
    fseek(newAudioImage, bitmapFileHeader->bfOffBits+44, SEEK_SET);
    int *newImage = createFinalBitImage(bitmapInfoHeader->biHeight, bitmapInfoHeader->biWidth,wavData,sizeOfFIle-44);

    

    int count = 0;
    printf("height = %d, width = %d\n", bitmapInfoHeader->biHeight, bitmapInfoHeader->biWidth);

    for (int i = 0; i < bitmapInfoHeader->biSizeImage; i += 3) // fixed semicolon
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
    return (WAVdata);
}

#ifdef DEBUGAUDIO
int main()
{
    encodeAudio("Untitled.bmp", "Tainted_Love.wav");
}
#endif // DEBUG
