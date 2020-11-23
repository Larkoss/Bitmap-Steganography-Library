#include "partC.h"
#include <math.h>

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

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void FlipColumn(int **array, int column, int rows)
{
	// Flip column 'column' of an array that has n rows.
	for (int row = 0; row < rows / 2; row++)
	{
		swap(array[row] + column, array[rows - 1 - row] + column);
	}
}

void VFlipArray(int **array, int columns, int rows)
{
	for (int column = 0; column < columns; column++)
	{
		FlipColumn(array, column, rows);
	}
}

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
	return bitImage;
}

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
}