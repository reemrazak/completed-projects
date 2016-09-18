#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 1024
int rightChild(int value);
int leftChild(int value);
void printArray(int * array);

int main(int argc, char * argv[])
{
    
    FILE * file;
    int array[21][10];
    int i;
    int j;
    int h = 0;
    int temp;
    int * arrayPointer;
    int objectSum;
    int rightSum;
    int leftSum;
    printf("Hello\n");

    //Opens file from command line
    if (argc != 2)
    {
        printf("Please specify a file\n");
        exit(1);
    }
    file = fopen(argv[1], "r");
    if(file == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }
    //Get from file and store in 2d array
    for(i = 1; i<21; i = i+1)
    {
        for(j = 0; j<10; j = j+1)
        {
            fscanf(file, "%d", &array[i][j]);
        }
    }

    arrayPointer = *array;
    //printArray before sort
    printArray(arrayPointer);
    while(h<20)
    {
        i = 1;
        j = 0;
        while(i<21)
        {
            //compare the sum of the object to it's right child, if it is greater, swap the elements in the objects
            objectSum = array[i][0] + array[i][1] + array[i][2];
            rightSum = array[rightChild(i)][0] + array[rightChild(i)][1] + array[rightChild(i)][2];
            leftSum = array[leftChild(i)][0] + array[leftChild(i)][1] + array[leftChild(i)][2];
            if(objectSum > rightSum && rightChild(i)<=20)
            {
                j = 0;
                while(j<10)
                {
                    temp = array[i][j];
                    array[i][j] = array[rightChild(i)][j];
                    array[rightChild(i)][j] = temp;
                    j++;
                }
            }
            //compare the sum of the object to it's left child, if it is greater, swap the elements in the objects
            else if(objectSum > leftSum && leftChild(i)<=20)
            {
                j = 0;
                while(j<10)
                {
                    temp = array[i][j];
                    array[i][j] = array[leftChild(i)][j];
                    array[leftChild(i)][j] = temp;
                    j++;
                }
            }
            i++;
        }
        h++;
    }
    printf("\n\n\n");
    arrayPointer = *array;
    //prints the newly sorted array
    printArray(arrayPointer);

    fclose(file);
    return 0;
}

/*printArray prints every element of the array that it receives as a parameter*/
void printArray(int * array)
{
    int i;
    int j;
    for(i = 1; i<21; i = i+1)
    {
        for(j = 0; j<10; j = j+1)
        {
            printf("%d ", *((array+i*10) + j));
        }
        printf("\n");
    }
}
/*Calculates the position of the left child*/
int leftChild(int position)
{
    int rightChild = position*2;
    return rightChild;
}

/*Calculates the position of the right child*/
int rightChild(int position)
{
    int leftChild;
    leftChild = ((position * 2) +1);
    return leftChild;
}

