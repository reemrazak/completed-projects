//************************** CIS*3110- ASSIGNMENT 2 ***********************************//
//
//  Name:       Reem Razak
//  ID:         0851987
//**************************************************************************//
#include <stdlib.h>
#include <stdio.h>

#define NEW 0
#define READY 1
#define RUNNING 2
#define BLOCKED 3
#define TERMINATED 4

typedef struct Thread
{
	int threadNumber;
	int arrivalTime;
	int CPUTime;
	int IOTime;
	int processNumber;
	struct Thread * next;
}Thread;

typedef struct Queue
{
	struct Thread * theThread;
	struct Queue * next;
	struct Queue * previous;
	int status;
}Queue;

typedef struct Process
{
	int processNumber;
	int numThreads;
	int processTime;
	struct Process * next;
	struct Thread * firstThread;

}Process;

void enQueue(struct Queue ** front, struct Queue ** rear, struct Thread * theThread);
void deQueue(struct Process ** front, struct Process ** rear);
struct Thread * addThread(struct Thread * theList, struct Queue ** front, struct Queue ** rear, int threadNumber, int arrivalTime, int CPUTime, int IOTime, int processNumber, int quantum);
void destroyThreads(Thread * theList);
struct Process * addProcess(struct Process * theList,  int numThreads, int processNumber);
void destroyProcess(Process * theList);
void runSimulation(struct Queue * rear, int processSwitchTime, int threadSwitchTime, char mode, int numberOfProcesses, int CPUUtil);
struct Thread * robinQueue(struct Thread ** theList, struct Queue ** front, struct Queue ** rear, struct Thread ** theThread, int quantum);


