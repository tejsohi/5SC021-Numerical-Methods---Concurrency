//Importing librairies to be used in the program
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "lodepng.h"

//declaring a global variable and struct to be used later in the program.
unsigned char imageArray[5000000];

struct sVars
{
	int start;
	int finish;
	unsigned int width;
	unsigned int height;
	unsigned char *structImage;
	// unsigned char* imageArray;
};

/*
This method has no return type. 
This function takes the imagedata that is inputted by the user and
uses the box blur or gausian blur method to blur the image.


*/
void *BlurImage(void *arg)
{

	struct sVars *threadStruct = (struct sVars *)arg;
	int r, g, b, t;
	unsigned char *image = threadStruct->structImage;

	int height = threadStruct->height;
	int width = threadStruct->width;
	//unsigned char * imageArray=malloc(((threadStruct->finish-threadStruct->start)+1)*width*4*sizeof(unsigned char));
	//imageArray=threadStruct->imageArray;

	printf("start = %d  finish = %d\n", threadStruct->start, threadStruct->finish);

	for (int row = threadStruct->start; row <= threadStruct->finish; row++)
	{
		for (int col = 0; col < width * 4; col = col + 4)
		{
			r = image[(row * width * 4) + col];		//0
			g = image[(row * width * 4) + col + 1]; //1
			b = image[(row * width * 4) + col + 2]; //2
			t = image[(row * width * 4) + col + 3]; //3

			if (row == 0 && (col >= 0 && col < 4))
			{ // top left corner
				imageArray[(row * width * 4) + col] = (r + image[(row * width * 4) + col + 4] + image[(row + 1 * width * 4) + col] + image[(row + 1 * width * 4) + col + 4]) / 4;
				imageArray[(row * width * 4) + col + 1] = (g + image[(row * width * 4) + col + 1 + 4] + image[(row + 1 * width * 4) + col + 1] + image[(row + 1 * width * 4) + col + 1 + 4]) / 4;
				imageArray[(row * width * 4) + col + 2] = (b + image[(row * width * 4) + col + 2 + 4] + image[(row + 1 * width * 4) + col + 2] + image[(row + 1 * width * 4) + col + 2 + 4]) / 4;
				imageArray[(row * width * 4) + col + 3] = (t + image[(row * width * 4) + col + 3 + 4] + image[(row + 1 * width * 4) + col + 3] + image[(row + 1 * width * 4) + col + 3 + 4]) / 4;
			}
			else if (row == 0 && (col >= ((width * 4) - 4) && col <= ((width * 4) - 1)))
			{ // top right corner
				imageArray[(row * width * 4) + col] = (r + image[(row * width * 4) + col - 4] + image[(row + 1 * width * 4) + col - 4] + image[(row + 1 * width * 4) + col]) / 4;
				imageArray[(row * width * 4) + col + 1] = (g + image[(row * width * 4) + col + 1 - 4] + image[(row + 1 * width * 4) + col + 1 - 4] + image[(row + 1 * width * 4) + col + 1]) / 4;
				imageArray[(row * width * 4) + col + 2] = (b + image[(row * width * 4) + col + 2 - 4] + image[(row + 1 * width * 4) + col + 2 - 4] + image[(row + 1 * width * 4) + col + 2]) / 4;
				imageArray[(row * width * 4) + col + 3] = (t + image[(row * width * 4) + col + 3 - 4] + image[(row + 1 * width * 4) + col + 3 - 4] + image[(row + 1 * width * 4) + col + 3]) / 4;
			}
			else if (row == 0 && col >= 4 && col < ((width * 4) - 4))
			{ // top row middle cols
				imageArray[(row * width * 4) + col] = (r + image[(row * width * 4) + col - 4] + image[(row + 1 * width * 4) + col - 4] + image[(row + 1 * width * 4) + col] + image[(row + 1 * width * 4) + col + 4] + image[(row * width * 4) + col + 4]) / 6;
				imageArray[(row * width * 4) + col + 1] = (g + image[(row * width * 4) + col + 1 - 4] + image[(row + 1 * width * 4) + col + 1 - 4] + image[(row + 1 * width * 4) + col + 1] + image[(row + 1 * width * 4) + col + 1 + 4] + image[(row * width * 4) + col + 1 + 4]) / 6;
				imageArray[(row * width * 4) + col + 2] = (b + image[(row * width * 4) + col + 2 - 4] + image[(row + 1 * width * 4) + col + 2 - 4] + image[(row + 1 * width * 4) + col + 2] + image[(row + 1 * width * 4) + col + 2 + 4] + image[(row * width * 4) + col + 2 + 4]) / 6;
				imageArray[(row * width * 4) + col + 3] = (t + image[(row * width * 4) + col + 3 - 4] + image[(row + 1 * width * 4) + col + 3 - 4] + image[(row + 1 * width * 4) + col + 3] + image[(row + 1 * width * 4) + col + 3 + 4] + image[(row * width * 4) + col + 3 + 4]) / 6;
			}
			else if (row == (height - 1) && (col >= 0 && col < 4))
			{ // bottom left corner
				imageArray[(row * width * 4) + col] = (r + image[(row - 1 * width * 4) + col] + image[(row - 1 * width * 4) + col + 4] + image[(row * width * 4) + col + 4]) / 4;
				imageArray[(row * width * 4) + col + 1] = (g + image[(row - 1 * width * 4) + col + 1] + image[(row - 1 * width * 4) + col + 1 + 4] + image[(row * width * 4) + col + 1 + 4]) / 4;
				imageArray[(row * width * 4) + col + 2] = (b + image[(row - 1 * width * 4) + col + 2] + image[(row - 1 * width * 4) + col + 2 + 4] + image[(row * width * 4) + col + 2 + 4]) / 4;
				imageArray[(row * width * 4) + col + 3] = (t + image[(row - 1 * width * 4) + col + 3] + image[(row - 1 * width * 4) + col + 3 + 4] + image[(row * width * 4) + col + 3 + 4]) / 4;
			}
			else if (row == (height - 1) && col >= ((width * 4) - 4) && col <= ((width * 4) - 1))
			{ //bottom right corner
				imageArray[(row * width * 4) + col] = (r + image[(row - 1 * width * 4) + col] + image[(row - 1 * width * 4) + col - 4] + image[(row * width * 4) + col - 4]) / 4;
				imageArray[(row * width * 4) + col + 1] = (g + image[(row - 1 * width * 4) + col + 1] + image[(row - 1 * width * 4) + col + 1 - 4] + image[(row * width * 4) + col + 1 - 4]) / 4;
				imageArray[(row * width * 4) + col + 2] = (b + image[(row - 2 * width * 4) + col + 2] + image[(row - 1 * width * 4) + col + 2 - 4] + image[(row * width * 4) + col + 2 - 4]) / 4;
				imageArray[(row * width * 4) + col + 3] = (t + image[(row - 1 * width * 4) + col + 3] + image[(row - 1 * width * 4) + col + 3 - 4] + image[(row * width * 4) + col + 3 - 4]) / 4;
			}
			else if (row == (height - 1) && (col >= 4 && col < ((width * 4) - 4)))
			{ // bottom row middle cols
				imageArray[(row * width * 4) + col] = (r + image[(row * width * 4) + col - 4] + image[(row - 1 * width * 4) + col - 4] + image[(row - 1 * width * 4) + col] + image[(row - 1 * width * 4) + col + 4] + image[(row * width * 4) + col + 4]) / 6;
				imageArray[(row * width * 4) + col + 1] = (g + image[(row * width * 4) + col + 1 - 4] + image[(row - 1 * width * 4) + col + 1 - 4] + image[(row - 1 * width * 4) + col + 1] + image[(row - 1 * width * 4) + col + 1 + 4] + image[(row * width * 4) + col + 1 + 4]) / 6;
				imageArray[(row * width * 4) + col + 2] = (b + image[(row * width * 4) + col + 2 - 4] + image[(row - 1 * width * 4) + col + 2 - 4] + image[(row - 1 * width * 4) + col + 2] + image[(row - 1 * width * 4) + col + 2 + 4] + image[(row * width * 4) + col + 2 + 4]) / 6;
				imageArray[(row * width * 4) + col + 3] = (t + image[(row * width * 4) + col + 3 - 4] + image[(row - 1 * width * 4) + col + 3 - 4] + image[(row - 1 * width * 4) + col + 3] + image[(row - 1 * width * 4) + col + 3 + 4] + image[(row * width * 4) + col + 3 + 4]) / 6;
			}
			else if (col >= 0 && col < 4)
			{ // first col any row 6 values in tot
				imageArray[(row * width * 4) + col] = (r + image[(row * width * 4) + col + 4] + image[(row + 1 * width * 4) + col] + image[(row + 1 * width * 4) + col + 4] + image[(row - 1 * width * 4) + col + 4] + image[(row - 1 * width * 4) + col]) / 6;
				imageArray[(row * width * 4) + col + 1] = (g + image[(row * width * 4) + col + 1 + 4] + image[(row + 1 * width * 4) + col + 1] + image[(row + 1 * width * 4) + col + 1 + 4] + image[(row - 1 * width * 4) + col + 1 + 4] + image[(row - 1 * width * 4) + col + 1]) / 6;
				imageArray[(row * width * 4) + col + 2] = (b + image[(row * width * 4) + col + 2 + 4] + image[(row + 1 * width * 4) + col + 2] + image[(row + 1 * width * 4) + col + 2 + 4] + image[(row - 1 * width * 4) + col + 2 + 4] + image[(row - 1 * width * 4) + col + 2]) / 6;
				imageArray[(row * width * 4) + col + 3] = (t + image[(row * width * 4) + col + 3 + 4] + image[(row + 1 * width * 4) + col + 3] + image[(row + 1 * width * 4) + col + 3 + 4] + image[(row - 1 * width * 4) + col + 3 + 4] + image[(row - 1 * width * 4) + col + 3]) / 6;
			}
			else if (col >= ((width * 4) - 4) && col <= ((width * 4) - 1))
			{ // last col any row 6 values in tot
				imageArray[(row * width * 4) + col] = (r + image[(row * width * 4) + col - 4] + image[(row - 1 * width * 4) + col] + image[(row - 1 * width * 4) + col - 4] + image[(row + 1 * width * 4) + col - 4] + image[(row + 1 * width * 4) + col]) / 6;
				imageArray[(row * width * 4) + col + 1] = (g + image[(row * width * 4) + col + 1 - 4] + image[(row - 1 * width * 4) + col + 1] + image[(row - 1 * width * 4) + col + 1 - 4] + image[(row + 1 * width * 4) + col + 1 - 4] + image[(row + 1 * width * 4) + col + 1]) / 6;
				imageArray[(row * width * 4) + col + 2] = (b + image[(row * width * 4) + col + 2 - 4] + image[(row - 1 * width * 4) + col + 2] + image[(row - 1 * width * 4) + col + 2 - 4] + image[(row + 1 * width * 4) + col + 2 - 4] + image[(row + 1 * width * 4) + col + 2]) / 6;
				imageArray[(row * width * 4) + col + 3] = (t + image[(row * width * 4) + col + 3 - 4] + image[(row - 1 * width * 4) + col + 3] + image[(row - 1 * width * 4) + col + 3 - 4] + image[(row + 1 * width * 4) + col + 3 - 4] + image[(row + 1 * width * 4) + col + 3]) / 6;
			}
			else
			{
				imageArray[(row * width * 4) + col] = (r + image[((row + 1) * width * 4) + col] + image[((row + 1) * width * 4) + col + 4] + image[(row * width * 4) + col + 4] + image[((row - 1) * width * 4) + col + 4] + image[((row - 1) * width * 4) + col] + image[((row - 1) * width * 4) + col - 4] + image[(row * width * 4) + col - 4] + image[((row + 1) * width * 4) + col - 4]) / 9;
				imageArray[(row * width * 4) + col + 1] = (g + image[((row + 1) * width * 4) + col + 1] + image[((row + 1) * width * 4) + col + 1 + 4] + image[(row * width * 4) + col + 1 + 4] + image[((row - 1) * width * 4) + col + 1 + 4] + image[((row - 1) * width * 4) + col + 1] + image[((row - 1) * width * 4) + col + 1 - 4] + image[(row * width * 4) + col + 1 - 4] + image[((row + 1) * width * 4) + col + 1 - 4]) / 9;
				imageArray[(row * width * 4) + col + 2] = (b + image[((row + 1) * width * 4) + col + 2] + image[((row + 1) * width * 4) + col + 2 + 4] + image[(row * width * 4) + col + 2 + 4] + image[((row - 1) * width * 4) + col + 2 + 4] + image[((row - 1) * width * 4) + col + 2] + image[((row - 1) * width * 4) + col + 2 - 4] + image[(row * width * 4) + col + 2 - 4] + image[((row + 1) * width * 4) + col + 2 - 4]) / 9;
				imageArray[(row * width * 4) + col + 3] = (t + image[((row + 1) * width * 4) + col + 3] + image[((row + 1) * width * 4) + col + 3 + 4] + image[(row * width * 4) + col + 3 + 4] + image[((row - 1) * width * 4) + col + 3 + 4] + image[((row - 1) * width * 4) + col + 3] + image[((row - 1) * width * 4) + col + 3 - 4] + image[(row * width * 4) + col + 3 - 4] + image[((row + 1) * width * 4) + col + 3 - 4]) / 9;
			}
		}
	}

	pthread_exit(0);
}

void main(int argc, char **argv)
{

	unsigned char *image;
	unsigned int width, height;
	const char *filename = argv[1];
	const char *newFilename = argv[2];

	lodepng_decode32_file(&image, &width, &height, filename);

	int totalVals = height;
	int threadCount = atoi(argv[3]);
	if (threadCount > height)
	{
		threadCount = height;
	}
	int sliceList[threadCount];
	int remainder = totalVals % threadCount;

	for (int i = 0; i < threadCount; i++)
	{
		sliceList[i] = totalVals / threadCount;
	}

	for (int j = 0; j < remainder; j++)
	{
		sliceList[j] = sliceList[j] + 1;
	}

	int startList[threadCount];
	int finishList[threadCount];

	for (int k = 0; k < threadCount; k++)
	{
		if (k == 0)
		{
			startList[k] = 0;
			finishList[k] = startList[k] + sliceList[k] - 1;
		}
		else
		{
			startList[k] = finishList[k - 1] + 1;
			finishList[k] = startList[k] + sliceList[k] - 1;
		}
	}

	struct sVars threadArgs[threadCount];

	for (int s = 0; s < threadCount; s++)
	{ //create structs
		threadArgs[s].structImage = image;
		threadArgs[s].start = startList[s];
		threadArgs[s].finish = finishList[s];
		threadArgs[s].width = width;
		threadArgs[s].height = height;
	}

	pthread_t tids[threadCount];

	for (int t = 0; t < threadCount; t++)
	{
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&tids[t], &attr, BlurImage, &threadArgs[t]);
	}
	//unsigned char *ImageOutput = malloc(height * width * 4 * sizeof(unsigned char *));
	for (int t = 0; t < threadCount; t++)
	{
		pthread_join(tids[t], NULL);
		/**	for (int row=startList[t]; row <=finishList[t]; row++)
						{
							for (int col = 0; col < width * 4; col++)
							{
								ImageOutput[(row * width * 4) + col]=threadArgs[t].imageArray[(row * width * 4) + col];
							}
						}	**/
	}

	lodepng_encode32_file(newFilename, imageArray, width, height);

	free(image);
}
