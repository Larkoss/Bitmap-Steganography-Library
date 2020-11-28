#include "wav.h"

void encodeAudio(char *pictureName, char *AudioFile){

    BITMAPINFOHEADER *bitmapInfoHeader = (BITMAPINFOHEADER *)malloc(sizeof(BITMAPINFOHEADER));
    BITMAPFILEHEADER *bitmapFileHeader = (BITMAPFILEHEADER *)malloc(sizeof(BITMAPFILEHEADER));
    byte *bitmapImage = LoadBitmapFile(pictureName, bitmapInfoHeader, bitmapFileHeader);

    WAVHEADER *wavHeader = (WAVHEADER *)malloc(sizeof(WAVHEADER));
    long sizeOfFIle = 0;
    unsigned char *wavData = LoadWavFile(AudioFile,wavHeader,&sizeOfFIle);

    FILE *output = fopen("music.wav","w");
    fwrite(wavHeader,sizeof(WAVHEADER),1,output);
    
    fseek(output,44,SEEK_SET);
    for(int i=0;i<sizeOfFIle;i++){
        fputc(wavData[i],output);
    }

    


}

unsigned char  *LoadWavFile(char *WAVfilename,WAVHEADER *header,long *size){
    unsigned char  *WAVdata;
    FILE *WAVFile = fopen(WAVfilename,"rb");

    fread(header,sizeof(WAVHEADER),1,WAVFile);

    fseek(WAVFile,44,SEEK_SET);

    fseek(WAVFile,0,SEEK_END);
    long sizeFile = ftell(WAVFile);
    fseek(WAVFile,44,SEEK_SET);


    WAVdata = (unsigned char  *)malloc(sizeFile);
    fread(WAVdata,sizeFile-44,1,WAVFile);

    *size = sizeFile;
    return(WAVdata);

}

int main(){
    encodeAudio("awd","Tainted_Love.wav");
}