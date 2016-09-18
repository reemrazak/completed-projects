//************************** CIS*3110- ASSIGNMENT 2 ***********************************//
//
//  Name:       Reem Razak
//  ID:         0851987
//**************************************************************************//

#include "a2.h"
#include "List.h"
int main(int argc, char * argv[])
{

	int i, j, k;
	int defaultMode = 0;
	int detailedMode = 0;
	int robinMode = 0;
	int verboseMode = 0;
	int quantum = 0;
	int numberOfProcesses;
	int threadSwitchTime;
	int processSwitchTime;
	int CPUUtil = 0;

	int processNum;
	int threadNum;
	int numThreads;
	int arrivalTime;
	int numCPU;
	int CPUTime, CPUCounter;
	int IOTime, IOCounter;

	struct Process * head = NULL;
	struct Queue * front =  NULL;
	struct Queue * rear = NULL;
	char * string = malloc(sizeof(char) * MAX_BUFFER);

	for(i = 1; i < argc; i++)
	{
		if(strcmp(argv[i], "-d") == 0)
		{
			detailedMode = 1; //Detailed mode was requested by the user
		}
		else if(strcmp(argv[i], "-r") == 0)
		{
			robinMode = 1; //Round Robin mode was requested by the user
			quantum = atoi(argv[i + 1]);
			i++;
		}
		else if(strcmp(argv[i], "-v") == 0)
		{
			verboseMode = 1;//Verbose mode was requested by the user
		}
		else
		{
			printf("You have provided invalid arguments\n");
			exit(0);
		}
	}
	if((detailedMode == 0) && (verboseMode == 0))
	{
		defaultMode = 1; //if nothing was requested by the user, the simulation is set to default mode
	}

/*Scan the first three numbers in the file to get the total number of processes, and thread & process switch time*/
	fgets(string, MAX_BUFFER, stdin);
	sscanf(string, "%d %d %d", &numberOfProcesses, &threadSwitchTime, &processSwitchTime);
	for(i = 0; i < numberOfProcesses; i++)
	{
		/*For each process, get the process number and number of threads, and store in the
		process linked list*/
		fgets(string, MAX_BUFFER, stdin);
		sscanf(string, "%d %d", &processNum, &numThreads);
		head = addProcess(head,  numThreads,  processNum);

		for(j = 0; j < numThreads; j++)
		{
			/*For each thread within a process, get the thread number, arrival time, and number of
			CPU bursts*/
			fgets(string, MAX_BUFFER, stdin);
			sscanf(string, "%d %d %d", &threadNum, &arrivalTime, &numCPU);
			CPUTime = 0;
			IOTime = 0;
			for(k = 0; k < numCPU - 1; k++)
			{
				/*For each cpu burst within a thread, get the number of units of the CPU and IO time and add to counters*/
				fgets(string, MAX_BUFFER, stdin);
				sscanf(string, "%*d %d %d", &CPUCounter, &IOCounter);
				CPUTime = CPUTime + CPUCounter;
				IOTime = IOTime + IOCounter;
			}
			fgets(string, MAX_BUFFER, stdin);
			sscanf(string, "%*d %d", &CPUCounter);
			CPUTime = CPUTime + CPUCounter;
			CPUUtil = CPUTime + CPUUtil;
			if(robinMode == 1)
			{
				head->firstThread = addThread(head->firstThread, &front, &rear, threadNum, arrivalTime, CPUTime, IOTime, processNum, quantum);	
			}
			else
			{
				head->firstThread = addThread(head->firstThread, &front, &rear, threadNum, arrivalTime, CPUTime, IOTime, processNum, -1);			
			}
		}
	}

	if(robinMode == 1)
	{
		printf("\nRound Robin (quantum = %d time units)\n\n", quantum);
	}
	else
	{
		printf("\nFCFS:\n\n");
	}
	if(defaultMode == 1)
	{
		runSimulation(rear, processSwitchTime, threadSwitchTime, 'o', numberOfProcesses, CPUUtil);
	}
	else if(detailedMode == 1)
	{

		runSimulation(rear, processSwitchTime, threadSwitchTime, 'o', numberOfProcesses, CPUUtil);
		runSimulation(rear, processSwitchTime, threadSwitchTime, 'd', numberOfProcesses, CPUUtil);
	}
	else if(verboseMode == 1)
	{
		runSimulation(rear, processSwitchTime, threadSwitchTime, 'v', numberOfProcesses, CPUUtil);
	}

	destroyProcess(head);
	free(string);

	return 0;
}




