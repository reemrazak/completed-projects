//************************** CIS*3110- ASSIGNMENT 2 ***********************************//
//
//  Name:       Reem Razak
//  ID:         0851987
//**************************************************************************//
#include "Queue.h"

//make copy
//print  simulated q
//print  regular q
//isempty

void enQueue(struct Queue ** front, struct Queue ** rear, int sizeMB, int timesSwapped, int age, int location, char pid)
{
    struct Queue * new;
    new = malloc(sizeof(struct Queue));

    new->sizeMB = sizeMB;
    new->timesSwapped = timesSwapped;
    new->age = age;
    new->location = location;
    new->pid = pid;
    new->next = NULL;
    new->previous = NULL;

/*If queue is empty then the new node is both the front and rear of the queue*/
    if((*front) == NULL)
    {
    	(*front) = new;
    	(*rear) = (*front);
    }
    else
    {
		(*rear)->next = new;
		new->previous = (*rear);
		(*rear) = new;
    }
}
void printQueue(struct Queue* front)
{
	struct Queue * temp;
	temp = front;
	printf("\n\n");
	while(temp->next != NULL)
	{
		printf("Process: %c Size: %d\n", temp->pid, temp->sizeMB);
		temp = temp->next;
	}
	printf("Process: %c Size: %d\n", temp->pid, temp->sizeMB);
}

void destroyQueue(struct Queue ** front, struct Queue ** rear)
{
	struct Queue * current;
	struct Queue * next;
	current = (*front);
	next = (*front)->next;
	while(current->next != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	free(current);
	current = NULL;
	front = NULL;
}
struct Queue * deQueue(struct Queue ** front)
{
	if(((*front)->next != NULL) && (front != NULL))
	{
		(*front) = (*front)->next;
		return (*front);
	}
	return NULL;
}

struct List * addProcess(struct List * theList,  int numThreads, int processNumber)
{
	struct List * newProcess;
	struct List * temp;
	temp = theList;
	newProcess = malloc(sizeof(struct List));
	newProcess->numThreads = numThreads;
	newProcess->processNumber = processNumber;
	newProcess->processTime = 0;
	newProcess->next = NULL;
	if(newProcess == NULL)
	{
		return NULL;
	}
	/*Add the process to the end of the linked list using a simple traversal*/
	if(theList != NULL)
	{
		while(temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = newProcess;
	}
	else
	{
		return newProcess;
	}
	return theList;
}



void destroyList(List * theList)
{
	List * current;
	List * next;
	current = theList;
	next = theList->next;
	while(current->next != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	free(current);
	current = NULL;
	theList = NULL;
}



