//************************** CIS*3110- ASSIGNMENT 2 ***********************************//
//
//  Name:       Reem Razak
//  ID:         0851987
//**************************************************************************//
#include "List.h"
void enQueue(struct Queue ** front, struct Queue ** rear, struct Thread * theThread)
{
    struct Queue * new;
    struct Queue * temp;
    new = malloc(sizeof(struct Queue));

    new->next = NULL;
    new->previous = NULL;
    new->status = -1;
    new->theThread = theThread;

/*If queue is empty then the new node is both the front and rear of the queue*/
    if((*front) == NULL)
    {
    	(*front) = new;
    	(*rear) = (*front);
    }
    else
    {
    	temp = (*front);
    	if(theThread->arrivalTime > temp->theThread->arrivalTime)//new thread has higher arrival time
    	{
    		(*front)->previous = new;
    		new->next = (*front);
    		(*front) = new;
    	}
    	else
    	{
    		while(theThread->arrivalTime < temp->theThread->arrivalTime)//cycle through the arrival times to find the correct placement
    		{
    			if(temp->next == NULL)
    			{
    				break;
    			}
    			temp = temp->next;
    		}
    		if((temp->next == NULL) && (new->theThread->arrivalTime < temp->theThread->arrivalTime))
    		{
    			(*rear)->next = new;
    			new->previous = (*rear);
    			(*rear) = new;
    		}
    		else
    		{
    			temp->previous->next = new;
    			new->previous = temp->previous;
    			new->next = temp;
    			temp->previous = new;
    		}
    	}
    }
}

void deQueue(struct Process ** front, struct Process ** rear)
{
	struct Process * temp = (*rear);
	if((*rear) != NULL)
	{
		destroyThreads((*rear)->firstThread);
		(*rear) = (*rear)->next;
		free(temp);
	}
}

struct Process * addProcess(struct Process * theList,  int numThreads, int processNumber)
{
	struct Process * newProcess;
	struct Process * temp;
	temp = theList;
	newProcess = malloc(sizeof(struct Process));
	newProcess->numThreads = numThreads;
	newProcess->processNumber = processNumber;
	newProcess->processTime = 0;
	newProcess->next = NULL;
	newProcess->firstThread = NULL;
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

struct Thread * addThread(struct Thread * theList, struct Queue ** front, struct Queue ** rear, int threadNumber, int arrivalTime, int CPUTime, int IOTime, int processNumber, int quantum)
{
    struct Thread * newThread;
    struct Thread * temp;
    temp = theList;
    newThread = malloc(sizeof(struct Thread));
    newThread->threadNumber = threadNumber;
    newThread->arrivalTime = arrivalTime;
    newThread->CPUTime = CPUTime;
    newThread->IOTime = IOTime;
    newThread->processNumber = processNumber;
    newThread->next = NULL;

    if(newThread == NULL)
    {
        return NULL;
    }
	/*Add the thread to the end of the linked list using a simple traversal*/
    if(theList != NULL)
    {
	    while(temp->next != NULL)
	    {
	    	temp = temp->next;
	    }
    	temp->next = newThread;
    }
    else
    {
    	if(quantum == -1)
    	{
			enQueue(front, rear, newThread);
		}
		else
		{
			 robinQueue(&theList, front, rear, &newThread, quantum);
		}
    	return newThread;
    }
    /*Add the thread to the queue list*/
	if(quantum == -1)
	{
		enQueue(front, rear, newThread);
	}
	else
	{
		 robinQueue(&theList, front, rear, &newThread, quantum);
	}
    return theList;
}

struct Thread * robinQueue(struct Thread ** theList, struct Queue ** front, struct Queue ** rear, struct Thread ** theThread, int quantum)
{
	int timeCounter;
	if((*theThread)->CPUTime <= quantum)
	{
		enQueue(front, rear, (*theThread));

	}
	else
	{
		timeCounter = (*theThread)->CPUTime;
		{
			while(timeCounter > quantum)
			{
				addThread((*theList), front, rear, (*theThread)->threadNumber, (*theThread)->arrivalTime, quantum, (*theThread)->IOTime, (*theThread)->processNumber, -1);
				timeCounter = timeCounter - quantum;
				printf("Time counter is %d\n", timeCounter);		
			}
			addThread((*theList), front, rear, (*theThread)->threadNumber, (*theThread)->arrivalTime, timeCounter, (*theThread)->IOTime, (*theThread)->processNumber, -1);
		}

	}
	return (*theList);
}
void destroyProcess(Process * theList)
{
	Process * current;
	Process * next;
	current = theList;
	next = theList->next;
	while(current->next != NULL)
	{
		next = current->next;
		destroyThreads(current->firstThread);
		free(current);
		current = next;
	}
	free(current);
	current = NULL;
	theList = NULL;
}
void destroyThreads(Thread * theList)
{
    Thread * current;
    Thread * next;
    current = theList;
    next = theList->next;
    while(current->next!=NULL)
    {
        next = current->next;
        free(current);
        current = next;        
    }
    free(current);
    current = NULL;
    
    theList = NULL;
}


void runSimulation(struct Queue * rear, int processSwitchTime, int threadSwitchTime, char mode, int numberOfProcesses, int CPUUtil)
{
	struct Queue *var=rear;
	struct Queue * temp = var;
	int currentTime = 0;
	int finishTime = 0;
	while(var!=NULL)
	{
		/*If in verbose mode, print out all the threads that up to this point in time which are in the new state.
		Also move them up to running IF possible*/
		if(mode == 'v')
		{
			while((temp != NULL) && (temp->theThread->arrivalTime <= currentTime))
			{
				printf("At time %d: Thread %d of Process %d moves from new to ready\n", temp->theThread->arrivalTime, temp->theThread->threadNumber, temp->theThread->processNumber);
				temp->status = NEW;
				temp = temp->previous;
			}
			printf("At time %d: Thread %d of Process %d moves from ready to running\n", currentTime, var->theThread->threadNumber, var->theThread->processNumber);
			var->status = RUNNING;
		}
		if(var->theThread->arrivalTime > currentTime)
		{
			currentTime = var->theThread->arrivalTime;
		}
		finishTime = currentTime + var->theThread->CPUTime + var->theThread->IOTime;
		if(mode == 'd')//if detailed
		{
			printf("Thread %d of Process %d:\n\n", var->theThread->threadNumber, var->theThread->processNumber);
			printf("arrival time: %d\nservice time: %d units\nI/O time: %d units\nturnaround time: %d units\nfinish time: %d units\n\n", var->theThread->arrivalTime, var->theThread->CPUTime, var->theThread->IOTime, (finishTime - var->theThread->arrivalTime), finishTime);
	    }
	    currentTime = finishTime;
	    /*If in verbose mode, again check if any threads are read to be moved from the new to ready state
	    Also check if they are ready to be terminated*/
	    if(mode == 'v')
	    {
			while((temp != NULL) && (temp->theThread->arrivalTime <= currentTime))
			{
				printf("At time %d: Thread %d of Process %d moves from new to ready\n", temp->theThread->arrivalTime, temp->theThread->threadNumber, temp->theThread->processNumber);
				temp->status = NEW;
				temp = temp->previous;
			}
			var->status = RUNNING;
			printf("At time %d: Thread %d of Process %d moves from running to terminated\n", currentTime, var->theThread->threadNumber, var->theThread->processNumber);
	    }
	    if((var->previous != NULL) && (var->theThread->processNumber != var->previous->theThread->processNumber))
	    {
	    	currentTime = currentTime + processSwitchTime;
	    }
	    else if(var->previous != NULL)
	    {
	    	currentTime = currentTime + threadSwitchTime;
	    }
	    var=var->previous;
	}
	/*If in default mode, print the total time, ave turn around, and cpu utilization*/
	if(mode == 'o')
	{
		printf("Total Time required is %d time units\n", currentTime);
		printf("Average Turnaround Time is %d time units\n", currentTime/numberOfProcesses);
		printf("CPU Utilization is %f%%\n", (float)CPUUtil/currentTime*100);
	}

}

