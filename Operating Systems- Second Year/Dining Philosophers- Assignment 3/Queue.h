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


typedef struct Queue
{
	struct Queue * next;
	struct Queue * previous;
	int sizeMB;
	int timesSwapped;
	int age;
	int location;
	char pid;
}Queue;

typedef struct List
{
	int processNumber;
	int numThreads;
	int processTime;
	struct List * next;

}List;

void enQueue(struct Queue ** front, struct Queue ** rear, int sizeMB, int timesSwapped, int age, int location, char pid);
void destroyQueue(struct Queue ** front, struct Queue ** rear);
struct List * addProcess(struct List * theList,  int numThreads, int processNumber);
void destroyList(List * theList);
void printQueue(struct Queue* front);
struct Queue * deQueue(struct Queue ** front);


