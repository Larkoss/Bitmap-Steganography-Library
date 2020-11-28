# HW4-Fall20
# Library bmlib.a
## Operation 1: Export meta-data
The –list argument refers to printing the header elements of a specified image in the following format.

$./bmpSteganography –list 4x3.bmp image2.bmp 

BITMAP_FILE_HEADER ================== <br />
bfType: BM <br />
bfSize: 104 <br />
bfReserved1: 0 <br />
bfReserved2: 0 <br />
bfOffBits: 54 <br />
BITMAP_INFO_HEADER ================== <br />
biSize: 40 <br />
biWidth: 3 <br />
biHeight: 4 <br />
biPlanes: 1 <br />
biBitCount: 24 <br />
biCompression: 0 biSizeImage: 50 <br />
biXPelsPerMeter: 2834 <br />
biYPelsPerMeter: 2834 <br />
biClrUsed: 0 <br />
biClrImportant: 0 <br />

## Operation 2: Grayscale Filter 
$./bmpSteganography –grayscale image1.bmp [ image2.bmp image3.bmp ...] 

The –grayscale argument applies the grayscale filter that converts the color of each pixel to shades of gray. To do this, each pixel must be converted to the following logic: Each pixel takes up 3 bytes (if 24bit color depth is used). In particular, these bytes are broken down as follows: red=1 byte, green=1 byte, blue=1 byte. These bytes are multiplied using the NTSC (National Television System Committee) equation: 0.299*red + 0.587*green + 0.114*blue. The rounded result of the NTSC equation on each individual 3-byte RGB sequence of the file will be called absolute brightness. For example, for an RGB= pixel(9,90,160), luminance is 0.299*9 + 0.587*90 + 0.114*160 = 73,761. Therefore, the gray version of the pixel must be (74,74,74). If we repeat the above equation for all pixels in an image we will get the result needed.
![alt text](https://i.imgur.com/roZPOsi.png)

## Operation 3: Encode a secret image within another image
$./bmpSteganography –encodeStegano nbBits coverImage.bmp secretImage.bmp 

The result of performing this operation is to create an image named newcoverImage.bmp which is the cover image with the secret image inside it. Its name is created by the name of the cover image by adding the prefix "new-" . The nbBits parameter shows the number of bits of the cover image that change by inserting so many more bits from the secret image.
![alt text](https://i.imgur.com/GPB7E20.png)

## Operation 4: Decoding/Retrieving a secret image from another image
$./bmpSteganography –decodeStegano nbBits encryptedImage.bmp 

The result of performing this operation is to create an image named newencryptedImage.bmp which is the secret image. Its name is created by the name of the cover image by adding the prefix "new-" . The nbBits parameter shows the number of bits of the cover image that change by inserting so many more bits from the secret image. 
![alt text](https://i.imgur.com/ZFrumMk.png)

## Operation 5: Encode text within an image
$./bmpSteganography –encodeText coverImage.bmp inputText.txt 

The result of performing this operation is to create an image named newcoverImage.bmp which is a bmp image with inputText text embedded in it.txt. Its name is created by the name of the cover image by adding the prefix "new-" .
![alt text](https://i.imgur.com/oavDjho.png)

## Operation 6: Decoding/Retrieving secret text from an image
$./bmpSteganography –decodeText encryptedImage.bmp msgLength output.txt 

 The result of performing this operation is to create a text file with the message retrieved from the encrypted Image encryptedImage.bmp. To do this operation, you must do the opposite procedure that you did for operation 6. To get the final text, you must know its length in characters, which is given to the command line by the msgLeggth parameter. The message must be the same in its format (same lines) as the message encoded in mode 6.
![alt text](https://i.imgur.com/z40EzEC.png)

## Operation 7: Create a bmp image from text
$./bmpSteganography –stringToImage sampleImage.bmp inputText.txt

This function implements what is described in section C. of Chapter IV. The text in the inputText .txt "converted" to a bmp image which will be a gray image. Note that the length of the text must be sufficient to fill the dimensions of the image and make a result visible to the naked eye. The sampleImage .bmp used only to assign the generated image the same values for the BITMAP_FILE_HEADER and BITMAP_INFO_HEADER.
![alt text](https://i.imgur.com/ztYmvre.png)

## Operation 8: Decoding/Retrieving secret text from a bmp image 
$./bmpSteganography –imageToString encryptedTextImage.bmp

A text file named outputText.txt is created.




