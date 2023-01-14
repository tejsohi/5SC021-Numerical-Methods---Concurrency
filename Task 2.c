//Compile program with gcc -o a.out 2.c -lm -pthread
//Run program e.g ./a.out (number of iterations) (number of threads)

//Importing librairies to be used in the program
#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>

//Declaring global variables to be used later in the program.
float pi = 0;
float approxPi;
pthread_mutex_t mutex;

//declaring a struct to be used later in the program
typedef struct
{
    int start;
    int finish;
} threadArgs;

/*
This method has no return type. 

This method is the method that uses the Leibniz formula to calculate PI
This method also makes use of multithreading.
*/
void *calcPi(void *fargs)
{
    int start;
    int finish;
    int i;

    threadArgs *tArgs = (threadArgs *)fargs;
    start = tArgs->start;
    finish = tArgs->finish;

    pthread_mutex_lock(&mutex);
    for (i = start; i < finish; i++)
    {
        pi += pow(-1, i) / (2 * i + 1);
    }
    pthread_mutex_unlock(&mutex);
    pthread_exit(0);
    return 0;
}

/*
This is the main function that will run at startup.
This method has and integer return type and args passed in.

The purpose of this method is to take in user input,
and use multithreading with appropriate slicing.
It then outputs the value of PI

*/
int main(int argc, char *argv[])
{

    //declaring and intialising variables and taking user input from args.
    int iterations, threadCount;
    int i;

    char *a = argv[1];
    char *b = argv[2];

    iterations = atoi(a);
    threadCount = atoi(b);

    /*Everything below this point is dealing with threading and slicing,
    and is also where the call for the calclating Pi is done.

    */
    int slices[threadCount];
    int remainder = iterations % threadCount;

    threadArgs tArgs[threadCount];

    pthread_t thread[threadCount];
    pthread_mutex_init(&mutex, NULL);

    for (i = 0; i < threadCount; i++)
    {
        slices[i] = iterations / threadCount;
    }

    for (i = 0; i < remainder; i++)
    {
        slices[i] += 1;
    }

    for (i = 0; i < threadCount; i++)
    {
        if (i == 0)
        {
            tArgs[i].start = 0;
        }
        else
        {
            tArgs[i].start = tArgs[i - 1].finish + 1;
        }
        tArgs[i].finish = tArgs[i].start + slices[i] - 1;
    }

    for (i = 0; i < threadCount; i++)
    {
        pthread_create(&thread[i], NULL, calcPi, &tArgs[i]);
    }

    for (i = 0; i < threadCount; i++)
    {
        pthread_join(thread[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    //An approximation of Pi is done and outputted.

    approxPi = pi * 4;

    printf("The approximate value of PI: %f\n", approxPi);
}