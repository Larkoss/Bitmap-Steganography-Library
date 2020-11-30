#ifndef BMPHEADERS_H
#define BMPHEADERS_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

typedef unsigned char byte;
typedef unsigned short int word;
typedef unsigned int dword;

typedef struct
{
    unsigned char riff[4];              // RIFF string
    unsigned int overall_size;          // overall size of file in bytes
    unsigned char wave[4];              // WAVE string
    unsigned char fmt_chunk_marker[4];  // fmt string with trailing null char
    unsigned int length_of_fmt;         // length of the format data
    unsigned int format_type;           // format type. 1-PCM, 3- IEEE float, 6 - 8bit A law, 7 - 8bit mu law
    unsigned int channels;              // no.of channels
    unsigned int sample_rate;           // sampling rate (blocks per second)
    unsigned int byterate;              // SampleRate * NumChannels * BitsPerSample/8
    unsigned int block_align;           // NumChannels * BitsPerSample/8
    unsigned int bits_per_sample;       // bits per sample, 8- 8bits, 16- 16 bits etc
    unsigned char data_chunk_header[4]; // DATA string or FLLR string
    unsigned int data_size;             // NumSamples * NumChannels * BitsPerSample/8 - size of the next chunk that will be read
}__attribute__((__packed__)) WAVHEADER;
typedef struct
{
    byte bfType1;
    byte bfType2;
    dword bfSize; //Specifies the size of the file (including padding) in bytes
    word bfReserved1;
    word bfReserved2;
    dword bfOffBits;//Specifies the offset from the beginning of the file to the bitmap data.

} __attribute__((__packed__)) BITMAPFILEHEADER;

typedef struct
{
    dword biSize;//Specifies the size of the BITMAPINFOHEADER structure, in bytes.
    dword biWidth;//Specifies the width of the image, in pixels.
    dword biHeight;//Specifies the height of the image, in pixels.
    word biPlanes;
    word biBitCount;//Specifies the number of bits per pixel.
    dword biCompression; //MUST BE 0 TO WORK!!
    dword biSizeImage;//Specifies the size of the image data, in bytes
    dword biXPelsPerMeter;
    dword biYPelsPerMeter;
    dword biClrUsed;
    dword biClrImportant;

}__attribute__((__packed__)) BITMAPINFOHEADER;

/**
 * @brief This function reads a BMP files and stores the file and info header to the appropriate structs. Then it reads the
 * data section of the image and imports it in a byte array.
 * 
 * @param BMPFileName  The name of the BMP file
 * @param bitmapInfoHeader The pointer to the Info header struct
 * @param bitmapFileHeader The pointer to the File header struct
 * @return byte* The data array with the bytes of the image
 */
byte *LoadBitmapFile(char *BMPFileName, BITMAPINFOHEADER *bitmapInfoHeader, BITMAPFILEHEADER *bitmapFileHeader);


/**
 * @brief A method to print the info and file headers of an Image
 * 
 * @param bitmapInfoHeader The Info header of the image
 * @param bitmapFileHeader The File header of the image
 */
void printMETA(BITMAPINFOHEADER *bitmapInfoHeader, BITMAPFILEHEADER *bitmapFileHeader);
/**
 * @brief Transforms an image to a grayscale representation of the given Image
 * 
 * @param imageName The name of the image file
 */
void grayscale(char *imageName);

/**
 * @brief Creates a bmp image from a given string file
 * 
 * @param imageName The name of the refference BMP file
 * @param strFile The name of the txt file that contains the string 
 */
void stringToImage(char *imageName, char *strFile);

/**
 * @brief Creates a txt file that includes the string representation of the given Image
 * 
 * @param imageName The name of the image file
 */
void imageToString(char *imageName);

/**
 * @brief Create a Final Bit Image object
 * 
 * @param height The height of the image that will be created
 * @param width The width of the image that will be created
 * @param imageData The string data that will be imported to create the image(Pointer)
 * @param biImageSize the size of the data header
 * @return int* The new data array that includes the bytes of the new generated image
 */
int *createFinalBitImage(int height, int width, char *imageData, int biImageSize);

/**
 * @brief Reverses the Pixels of the image
 * 
 * @param height The height of the image
 * @param width The width of the image
 * @param bitImage The array that contains the pixels of the image(Pointer)
 */
void reverseFinalBitImage(int height, int width, int *bitImage);

/**
 * @brief A Function that hides the n most significant bits of each byte of an image to the n least significant
 *  bits of each byte of the cover image. Outputs a new BMP file
 * 
 * @param nbBits The number of bits that will be hidden (0-8)
 * @param cover The name of the cover image file
 * @param secret The name of the secret image file
 */
void encodeStegano(int nbBits, char *cover, char *secret);

/**
 * @brief A function that creates a new BMP file that has the secret image decoded from the cover image
 * 
 * @param nbBits The number of bits that will be decoded from each byte of the cover photo
 * @param encryptedImage The name of the cover image file
 */
void decodeStegano(int nbBits, char *encryptedImage);

/**
 * @brief Get the n bit of a character
 * 
 * @param m A string 
 * @param n The bit you want to retreive
 * @return int The value of that bit (0 or 1)
 */
int getBit(char *m, int n);

/**
 * @brief Create a Permutation table that indicates the bytes of the image
 * 
 * @param N The size of the array that will be created
 * @param systemkey The seed that will be used to create the pseudorandom array
 * @return int* The permutation array
 */
int * createPermutationFunction(int N, unsigned int systemkey);

/**
 * @brief A function that hides text in an image. Uses getBit and createPermutationFunction
 * as described in pages 9 and 10 of the exercise's Instructions. Creates a new BMP file 
 * 
 * @param coverImageName The name of the cover image file
 * @param inputTextFileName The name of the text file that contains the string
 */
void encodeText(char *coverImageName, char *inputTextFileName);

/**
 * @brief Decodes text from an image. Creates a new txt file with given name that 
 * contains the encrypted message
 * 
 * @param encryptedImageName The name of the image file
 * @param msgLength The length of the message we want to retreive
 * @param outputFileName The name of the txt output file
 */
void decodeText(char *encryptedImageName, int msgLength, char *outputFileName);

//Extra operations
/**
 * @brief Creates a new file that has the red representation of the original image
 * 
 * @param imageName The name of the image file
 */
void redscale(char *imageName);
/**
 * @brief Creates a new file that has the green representation of the original image
 * 
 * @param imageName The name of the image file
 */
void greenscale(char *imageName);
/**
 * @brief Creates a new file that has the blue representation of the original image
 * 
 * @param imageName The name of the image file
 */
void bluescale(char *imageName);

int *createBitImage(int height, int width, char *image, int imageSize);
/**
 * @brief A method that creates a new BMP file generated from a WAV sound file!
 * 
 * @param pictureName The reference picture
 * @param AudioFile The WAV file name
 */
void encodeAudio(char *pictureName, char *AudioFile);

/**
 * @brief This fucntion generates a WAV file from an Image
 * 
 * @param BMPFileName The name of Image file
 */
void decodeAudio(char *BMPFileName);

/**
 * @brief A fucntion that reads a WAV audio file and extracts the header of the wav file to the 
 * appropriate struct and then returns a byte array with the data bytes of the file
 * 
 * @param WAVfilename The name of the audio file
 * @param header A pointer to the header of the file
 * @param size A pointer to return the size of the file
 * @return unsigned char* The arrayy that contains the data bytes of the file
 */
unsigned char *LoadWavFile(char *WAVfilename, WAVHEADER *header, long *size);



#endif