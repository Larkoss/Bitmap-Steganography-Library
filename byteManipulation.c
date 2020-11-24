//Purpose of this function is:
//1. Given an array of characters(the text of the file), transform it to array of bits
//2. Insert the bits into a 2d array that represents the pixel of the image
//3. Change the position of each bit to match the order explained in Question
//4. Put the bits back, in a 1d array
//5. Traverse the 1d array(in ) and set each pixel to 

#include "partC.h"
#include <math.h>


//Function to print array
void printArr(int **arr, int h, int w)
{
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
			printf("%d ", arr[i][j]);
		printf("\n");
	}
	printf("\n");
}

//Swap position of two elements in array
void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

//Swap each element of a row of the array
void FlipColumn(int **array, int column, int rows)
{
	// Flip column 'column' of an array that has n rows.
	for (int row = 0; row < rows / 2; row++)
	{
		swap(array[row] + column, array[rows - 1 - row] + column);
	}
}

//Mirror the array vertically.Swap first rows with last rows
void VFlipArray(int **array, int columns, int rows)
{
	for (int column = 0; column < columns; column++)
	{
		FlipColumn(array, column, rows);
	}
}

//Read a char array the represents the text of a file
//Turn each byte into bits. Fill the remaining with zeros.
int *createBitImage(int height, int width, char *image, int imageSize)
{
	int *bitImage = (int *)malloc(sizeof(int) * width * height * 8);
	char temp;
	for (int i = 0; i < imageSize; i++)
	{
		temp = image[i];
		for (int j = 0; j < 8; j++)
		{
			if (temp & 0x01)
				bitImage[i * 8 + j] = 1;
			else
			{
				bitImage[i * 8 + j] = 0;
			}
			temp >>= 1;
		}
		for (int j = 0; j < 4; j++)
		{
			int temp = bitImage[i * 8 + j];
			bitImage[i * 8 + j] = bitImage[i * 8 + 7 - j];
			bitImage[i * 8 + 7 - j] = temp;
		}
	}
	for (int i = imageSize * 8; i < width * height * 8; i++)
		bitImage[i] = 0;
	return bitImage;
}

//Take the array of bits created and modify it accordinly to be 
//ready to be insert in image
int *createFinalBitImage(int height, int width, char *imageData, int biImageSize)
{
	int h = height, w = width;
	int *bitImage = createBitImage(height, width, imageData, biImageSize);

	int **arr = (int **)malloc(h * sizeof(int *));
	for (int i = 0; i < h; i++)
		arr[i] = (int *)malloc(w * sizeof(int));

	int count = 0;
	for (int j = 0; j < w; j++)
	{
		for (int i = 0; i < h; i++)
		{
			arr[i][j] = bitImage[count++];
		}
	}

	//printArr(arr, h, w);
	VFlipArray(arr, w, h);
	//printArr(arr, h, w);

	count = 0;
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			bitImage[count++] = arr[i][j];
		}
	}

	//free
	for (int i = 0; i < h; i++)
		free(arr[i]);
	free(arr);
	return bitImage;
}

//Reverse engineer the above functions in order to get original bit array
//To swap back andn create array of characters(text).
void reverseFinalBitImage(int height, int width, int *bitImage)
{
	int h = height, w = width;
	int **arr = (int **)malloc(h * sizeof(int *));
	for (int i = 0; i < h; i++)
		arr[i] = (int *)malloc(w * sizeof(int));

	//
	int count = 0;
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			arr[i][j] = bitImage[count++];
		}
	}
	//printArr(arr, h, w);
	VFlipArray(arr, w, h);
	//printArr(arr, h, w);
	count = 0;
	for (int j = 0; j < w; j++)
	{
		for (int i = 0; i < h; i++)
		{
			bitImage[count++] = arr[i][j];
		}
	}

	//free
	for (int i = 0; i < h; i++)
		free(arr[i]);
	free(arr);
}