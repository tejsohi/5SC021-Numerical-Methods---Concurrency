//Importing librairies to be used in the program
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
This method has no return type. 
It has a single parameter of type integer

This method opens the first dataset and loops through every line.
Each number on each line are stored in a variable. 
After this, linear regresison is used to calculate the value of A & B.
And with User input, we are able to calucate Y

The values of A, B and Y are outputted
*/
void dataSetOne(int n)
{
  FILE *fptr;
  float x, y, m, c, d;
  float sumx, sumxsq, sumy, sumxy;

  char dataSetOne[50] = "datasetLR1.txt";

  fptr = fopen(dataSetOne, "r");

  while (fscanf(fptr, "%f, %f", &x, &y) != EOF)
  {
    sumx = sumx + x;
    sumxsq = sumxsq + (x * x);
    sumy = sumy + y;
    sumxy = sumxy + (x * y);
  }

  d = n * sumxsq - sumx * sumx;
  m = (n * sumxy - sumx * sumy) / d;
  c = (sumy * sumxsq - sumx * sumxy) / d;
  printf("M=%f\tC=%f\n", m, c);

  printf("dataset 1: y = %.0fx + %.0f \n", m, c);
  fclose(fptr);
}

/*
This method has no return type. 
It has a single parameter of type integer

This method opens the second dataset and loops through every line.
Each number on each line are stored in a variable. 
After this, linear regresison is used to calculate the value of A & B.
And with User input, we are able to calucate Y

The values of A, B and Y are outputted
*/
void dataSetTwo(int n)
{
  FILE *fptr;
  float x, y, m, c, d;
  float sumx, sumxsq, sumy, sumxy;
  char dataSetTwo[50] = "datasetLR2.txt";
  fptr = fopen(dataSetTwo, "r");

  while (fscanf(fptr, "%f, %f", &x, &y) != EOF)
  {
    sumx = sumx + x;
    sumxsq = sumxsq + (x * x);
    sumy = sumy + y;
    sumxy = sumxy + (x * y);
  }

  d = n * sumxsq - sumx * sumx;
  m = (n * sumxy - sumx * sumy) / d;
  c = (sumy * sumxsq - sumx * sumxy) / d;
  printf("M=%f\tC=%f\n", m, c);

  printf("dataset 2: y = %.0fx + %.0f \n", m, c);
  fclose(fptr);
}

/*
This method has no return type. 
It has a single parameter of type integer

This method opens the third dataset and loops through every line.
Each number on each line are stored in a variable. 
After this, linear regresison is used to calculate the value of A & B.
And with User input, we are able to calucate Y

The values of A, B and Y are outputted
*/
void dataSetThree(int n)
{
  FILE *fptr;
  float x, y, m, c, d;
  float sumx, sumxsq, sumy, sumxy;
  char dataSetThree[50] = "datasetLR3.txt";
  fptr = fopen(dataSetThree, "r");

  while (fscanf(fptr, "%f, %f", &x, &y) != EOF)
  {
    sumx = sumx + x;
    sumxsq = sumxsq + (x * x);
    sumy = sumy + y;
    sumxy = sumxy + (x * y);
  }

  d = n * sumxsq - sumx * sumx;
  m = (n * sumxy - sumx * sumy) / d;
  c = (sumy * sumxsq - sumx * sumxy) / d;
  printf("M=%f\tC=%f\n", m, c);

  printf("dataset 3: y = %.0fx + %.0f \n", m, c);
  fclose(fptr);
}

/*
This method has no return type. 
It has a single parameter of type integer

This method opens the fourth dataset and loops through every line.
Each number on each line are stored in a variable. 
After this, linear regresison is used to calculate the value of A & B.
And with User input, we are able to calucate Y

The values of A, B and Y are outputted
*/
void dataSetFour(int n)
{
  FILE *fptr;
  float x, y, m, c, d;
  float sumx, sumxsq, sumy, sumxy;
  char dataSetFour[50] = "datasetLR4.txt";
  fptr = fopen(dataSetFour, "r");

  while (fscanf(fptr, "%f, %f", &x, &y) != EOF)
  {
    sumx = sumx + x;
    sumxsq = sumxsq + (x * x);
    sumy = sumy + y;
    sumxy = sumxy + (x * y);
  }

  d = n * sumxsq - sumx * sumx;
  m = (n * sumxy - sumx * sumy) / d;
  c = (sumy * sumxsq - sumx * sumxy) / d;
  printf("M=%f\tC=%f\n", m, c);

  printf("dataset 4: y = %.0fx + %.0f \n", m, c);
  fclose(fptr);
}

/*
This is the main function that will run at startup.
This method has no return type or args

This method asks the user for a value of x which is stored in a variable.
The value of x is then passed in to each method call that reads that data sets.
*/
void main()
{

  float n;
  printf("Please enter in an 'n'(Number of points) value: ");
  scanf("%e", &n);
  printf("The value you entered was %.0f\n", n);

  dataSetOne(n);
  dataSetTwo(n);
  dataSetThree(n);
  dataSetFour(n);
}
