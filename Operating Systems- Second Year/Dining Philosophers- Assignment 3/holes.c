#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Queue.h"
#define BUFFER_SIZE 1024
#define MEMORY_SIZE 128

void firstFit(struct Queue ** front, struct Queue ** rear, struct Queue ** memoryQueue, int * memoryQueueSize, int * count);
void bestFit();
void worstFit();
void nextFit();
struct Queue * createQueue(struct Queue ** memoryQueue, struct Queue ** rear, struct Queue ** swap, int * size);
int calculate(int * memoryQueueSize, struct Queue ** theProcess, int * MEM, double * memUsage, int * counter, int * n, int * numProcesses, int * holeCt, double avgProcesses);
int spaceUsed(int * MEM, int * holes);
int main(int argc, char * argv[])
{
	FILE * input;
	struct Queue * front = NULL;
	struct Queue * rear = NULL;
	struct Queue * memoryQueue = NULL;
	char * string = malloc(sizeof(char)*BUFFER_SIZE);
	char * token;
	char pid;
	int sizeMB;
	int choice = -1;

	int theCounter = 0;
	int theSize = 0;


	if(argc != 2)
	{
		printf("Please specify a file when running the program\n");
		exit(1);
	}

	input = fopen(argv[1], "r");
	if(input == NULL)
	{
		printf("File not found\n");
		exit(1);
	}
	while(fgets(string, BUFFER_SIZE, input) != NULL)
	{
		token = strtok(string, " \n");
		pid = token[0];
		token = strtok(NULL, " \n");
		sizeMB = atoi(token);
		enQueue(&front, &rear, sizeMB, 0, 0, 0, pid);

	}

	while(choice != 0)
	{
		printf("\nPlease select an allocation strategy:\n1)Best- Fit\n2)Worst-Fit\n3)First-Fit\n4)Next-Fit\n0)Exit\n");
		scanf("%d", &choice);
		while((choice != 1) && (choice != 2) && (choice != 3) && (choice != 4) && (choice != 0))
		{
			printf("You must enter an integer from 1-4\n1)Best- Fit\n2)Worst-Fit\n3)First-Fit\n4)Next-Fit\n");
			scanf("%d", &choice);
		}

		memoryQueue = NULL;

		if(choice == 1)
		{
			bestFit();
			printQueue(front);
		}
		else if(choice == 2)
		{
			worstFit();
			printQueue(front);
		}
		else if(choice == 3)
		{
			firstFit(&front, &rear, &memoryQueue, &theSize, &theCounter);
		}
		else if(choice == 4)
		{
			nextFit();
			printQueue(front);
		}
	}
	destroyQueue(&front, &rear);
	free(string);
	fclose(input);
	return 0;
}

void bestFit()
{
	printf("NOW RUNNING BEST- FIT\n");

}
void firstFit(struct Queue ** front, struct Queue ** rear, struct Queue ** memoryQueue, int * memoryQueueSize, int * count)
{
	struct Queue * temp;
	struct Queue * previous;
	struct Queue * next;
	int MEM[MEMORY_SIZE] = {0};
	int i;
	int sizeEmpty;
	int emptyAddress;
	int loaded = 0;
	double usage = 0;
	double average = 0;
	int n = 0;
	int numProcesses = 0;
	int numHoles = 0;
	int oldest = 0;
	int oldestIndex;

	while(1)
	{
		sizeEmpty = 0;
		loaded = 0;
		average = 0;
		if(front == NULL)
		{
			break;
		}

		for(i = 0; i < 128; i++)
		{
			/*Finding available memory*/
			if(MEM[i] == 0)
			{
				sizeEmpty = sizeEmpty + 1;
				if(sizeEmpty == 1)
				{
					emptyAddress = i;
				}
			}
			else
			{
				sizeEmpty = 0;
			}

			if(sizeEmpty == (*front)->sizeMB)
			{
				(*front) = deQueue(front);

				(*front)->location = emptyAddress;

				//Filling out memory
				for(i = emptyAddress; i < (emptyAddress + (*front)->sizeMB); i++)
				{
					MEM[i] = 1;
				}

				(*memoryQueue) = createQueue(memoryQueue, rear, front, memoryQueueSize);
				printQueue(*memoryQueue);
				loaded = 1;
				break;
			}
		}
		if(loaded == 0)
		{
			(*count) = (*count) -1;
			//do shit
			temp = (*memoryQueue);
			//for(i=0; i < (*memoryQueueSize); i++)
			while((temp != NULL) && (temp->next != NULL))
			{					
				if(temp->age > oldest)
				{
					oldest = temp->age;
					oldestIndex = i;				// Save the index where the oldest is found
				}
				temp = temp->next;		
			}
			temp = (*memoryQueue);
			if(oldestIndex == 0)
			{
				if((*memoryQueue)->next == NULL)
				{
					(*memoryQueue) = NULL;	
				}
				else
				{
					(*memoryQueue) = (*memoryQueue)->next;
				}
			}
			else
			{
				i = 0;
				while((i != oldestIndex) && (temp->next != NULL))
				{
					temp = temp->next;
					i++;
				}

				previous = temp->previous;

				next = temp->next;
				previous->next = next;

				temp->next->previous = previous;

			}

			enQueue(front, rear,temp->sizeMB, temp->timesSwapped, temp->age, temp->location, temp->pid);

			for(i = oldestIndex; i < (oldestIndex + temp->age); i++)
			{
				MEM[i] = 0;
			}						

		}
		else if(loaded == 1)
		{
			calculate(memoryQueueSize, front, MEM, &usage, count, &n, &numProcesses, &numHoles, average);
		}
		temp = (*memoryQueue);
		i = 0;
		while((i != (*memoryQueueSize)) && (temp != NULL))
		{
			temp->age = temp->age + 1;
			temp = temp->next;
			i++;
		}

	}
	printf("NOW RUNNING FIRST- FIT\n");
}
void nextFit()
{
	printf("NOW RUNNING NEXT- FIT\n");

}
void worstFit()
{
	printf("NOW RUNNING WORST- FIT\n");

}

struct Queue * createQueue(struct Queue ** memoryQueue, struct Queue ** rear, struct Queue ** swap, int * size)
{
	if(memoryQueue == NULL)
	{
		(*memoryQueue) = (*swap);
		(*memoryQueue)->next = NULL;
		(*size) = 1;

	}
	else
	{
		enQueue(memoryQueue, rear, (*swap)->sizeMB, (*swap)->timesSwapped, (*swap)->age, (*swap)->location, (*swap)->pid);
		(*size) = (*size) + 1;
	}
	return (*memoryQueue);
}


int spaceUsed(int * MEM, int * holes)
{
	
	int i;
	int numBlocks = 0;
	
	for(i = 0; i < 128; i++)
	{
		if(MEM[i] == 1)
		{
			numBlocks = numBlocks + 1;
		}
		if(((MEM[i] == 0) && (MEM[i + 1] == 1) && ((i + 1) < 128)) || ((i == 127) && (MEM[i] == 0)))
		{		
			(*holes) = (*holes) + 1;
		}
	}	
	return numBlocks;
}

int calculate(int * memoryQueueSize, struct Queue ** theProcess, int * MEM, double * memUsage, int * counter, int * n, int * numProcesses, int * holes, double avgProcesses)
{
	
	int numHoles = 0;
	int memoryUsed = 0;
	double averageUse = 0;
	double newUse = 0;
	double avgHoles = 0;
		
	
	if(*theProcess == NULL)
	{
		return 0;
	} 
		
	(* n) = (* n) + 1;
	(*counter) = (*counter) + 1;

	memoryUsed = spaceUsed(MEM, &numHoles);

	newUse = ((double) memoryUsed / 128 ) * 100;	
	(* holes) = (* holes) + numHoles;	
	
	(* numProcesses) = (* numProcesses) + (* counter);	
	(* memUsage) = (* memUsage) + newUse; 
	avgHoles = ((double) * holes / (* n));
	

	avgProcesses = (* numProcesses)/(* n);						
	averageUse = (* memUsage)/(* n);

	printf("pid loaded, process ID = %c, #processes = %d, #holes = %d, %%memusage = %.1lf%%, cumulative %%mem = %.1lf%%\n", (*theProcess)->pid, (* memoryQueueSize), numHoles, newUse, averageUse);

	return 1;
}


