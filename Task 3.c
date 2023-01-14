//Importing librairies to be used in the program
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

//File pointers. 3 for reading data and 2 for writing data.
FILE *fp1;
FILE *fp2;
FILE *fp3;
FILE *fp4;
FILE *fp5;

//declaring a global variable and struct to be used later in the program.
int counter = 0;

typedef struct
{
    int start;
    int finish;
} args;

//function that detects prime numbers

/*
This method has no return type. 
This method takes a single parameter of type integer.

This function detects prime numbers and outputs them to a file.
*/
void PrimeOrNot(int prime)
{
    int i;
    int boolean = 0;

    if (i < 2)
    {
        boolean = 1;
    }

    //prime number detection from modulus
    for (i = 2; i < prime; i++)
    {
        if (prime % i == 0)
        {
            boolean = 1;
        }
    }

    //if remainder is 0 save to fp5
    if (boolean == 0)
    {
        fprintf(fp5, "%d\n", prime);
        counter++;
    }
}

//function that assigns values
void *func(void *fArgs)
{
    int start, finish;
    int i, num;

    //instance of struct to store structure type of data
    args *tArgs = (args *)fArgs;

    start = tArgs->start;
    finish = tArgs->finish;

    int *p = malloc(tArgs->start);
    int *p2 = malloc(tArgs->finish);

    for (i = start; i <= finish; i++)
    {
        fscanf(fp4, "%d\n", &num);
        PrimeOrNot(num);
    }

    pthread_exit(0);
    return 0;
}

/*
This is the main function that will run at startup.
This method has and integer return type and args passed in.

The purpose of this method is to take in user input,
and read and write from and to the relevant files when calculations have been completed
and use multithreading with slicing.

It then outputs to the user the total number of prime numbers.
*/
int main(int argc, char *argv[])
{
    int num, i;
    int lines = 0;
    int threadcount;

    char *a = argv[1];

    threadcount = atoi(a);

    int slices[threadcount];
    args tArgs[threadcount];

    pthread_t thread[threadcount];

    fp1 = fopen("PrimeData1.txt", "r");
    fp2 = fopen("PrimeData2.txt", "r");
    fp3 = fopen("PrimeData3.txt", "r");
    fp4 = fopen("Allnumbers.txt", "w");

    //reading from files pointers
    while (fscanf(fp1, "%d", &num) != EOF)
    {
        lines++;
    }

    while (fscanf(fp2, "%d", &num) != EOF)
    {
        lines++;
    }

    while (fscanf(fp3, "%d", &num) != EOF)
    {
        lines++;
    }

    int remainder = lines % threadcount;

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);

    fp1 = fopen("PrimeData1.txt", "r");
    fp2 = fopen("PrimeData2.txt", "r");
    fp3 = fopen("PrimeData3.txt", "r");
    fp5 = fopen("PrimeNumbers.txt", "w");

    //Slicing to each thread
    for (i = 0; i < threadcount; i++)
    {
        slices[i] = lines / threadcount;
    }

    for (i = 0; i < remainder; i++)
    {
        slices[i] += 1;
    }

    for (i = 0; i < threadcount; i++)
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

    //Reading from FILE pointers and printing on new file pointers
    while (fscanf(fp1, "%d", &num) != EOF)
    {
        fprintf(fp4, "%d\n", num);
    }

    while (fscanf(fp2, "%d", &num) != EOF)
    {
        fprintf(fp4, "%d\n", num);
    }

    while (fscanf(fp3, "%d", &num) != EOF)
    {
        fprintf(fp4, "%d\n", num);
    }

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);

    //Reading from the collected data
    fp4 = fopen("Allnumbers.txt", "r");

    //creating threads according to threadcount
    for (i = 0; i < threadcount; i++)
    {
        pthread_create(&thread[i], NULL, func, &tArgs[i]);
    }

    //Joining threads
    for (i = 0; i < threadcount; i++)
    {
        pthread_join(thread[i], NULL);
    }

    fprintf(fp5, "The total prime numbers: %d\n", counter);
    printf("The total prime numbers: %d\n", counter);

    fclose(fp4);
    fclose(fp5);
}
