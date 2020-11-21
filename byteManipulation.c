#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

typedef unsigned char byte;

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

int swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void FlipColumn(int **array, int column, int rows)
{
    // Flip column 'column' of an array that has n rows.
    for (int row = 0; row < rows/2; row++)
    {
        swap(array[row]+column, array[rows-1-row]+column);
    }
}

void VFlipArray(int **array, int columns, int rows)
{
    for (int column = 0; column < columns; column++)
    {
        FlipColumn(array, column, rows);
    }
}

int *createBitImage(byte *image, int imageSize)
{
	int *bitImage = (int *)malloc(sizeof(int) * imageSize * 8);
	int count = 0;
	byte temp;
	for(int i = 0; i < imageSize; i++)
	{
		temp = image[i];
		for(int j = 0; j < 8; j++)
		{
			if(temp & 0x01 == 1)
				bitImage[i * 8 + j] = 1;
			else
			{
				bitImage[i * 8 + j] = 0;
			}
			temp >>= 1;
			printf("%d ", bitImage[i * 8 + j]);
		}
		printf("\n");
	}
	printf("\n");
	return bitImage;
}


int main()
{
	int h = 4, w = 4;
	byte image[] = {'A', 'C'};
	int *bitImage = createBitImage(image, 2);
	
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
	printArr(arr, h, w);
	VFlipArray(arr, w, h); 
	printArr(arr, h, w);
	return 0;
}
