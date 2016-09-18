#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#define TRUE 1
#define FALSE 0

struct aPhil
{
    int philNum;
    int total;
    pthread_t * threads;
    pthread_mutex_t * forks;
}typedef aPhil;

void * philosopher(void * arg);
void eatingBigMacs(int philNum);
void philosophizing(int philNum);
aPhil * createPhilosopher(int philNum);
int isLastPhilosopher(aPhil * thePhilosopher);

int main(int argc, char * argv[])
{
	aPhil * philosophers;
	int numEats;
	int numPhils;
	int i;
	int j;

	if(argc != 3)
	{
		printf("Please run the program as follows: ./dine <number of philosophers> <number of times they eat>\n");
		exit(1);
	}
	numPhils = atoi(argv[1]);
	numEats = atoi(argv[2]);
	if((numPhils < 3) || (numEats < 1) || (numEats > 1000))
	{
		printf("Please ensure that the number of philosophers is greater than 2 and that the number of eats is from 1-1000\n");
		exit(1);
	}

	philosophers = createPhilosopher(numPhils);

	for(j = 0; j < numEats; j++)
	{
		for(i = 0; i < numPhils; i++)
		{
			philosophers->philNum = i;
			pthread_create(&philosophers->threads[i], NULL, &philosopher, philosophers);
			pthread_join(philosophers->threads[i], NULL);
		}
	}

	free(philosophers->threads);
	free(philosophers->forks);
	free(philosophers);
	return 0;

}
void philosophizing(int philNum)
{
	printf("Philosopher %d is thinking\n", (philNum + 1));
}

void eatingBigMacs(int philNum)
{
	printf("Philosopher %d is eating\n", (philNum + 1));
    sleep(1);
}

void * philosopher(void * arg)
{
	aPhil * thePhilosopher = arg;
    pthread_mutex_lock(&thePhilosopher->forks[thePhilosopher->philNum]);

	if(isLastPhilosopher(thePhilosopher))
	{
		pthread_mutex_lock(&thePhilosopher->forks[0]);
	}
	else
	{
		pthread_mutex_lock(&thePhilosopher->forks[thePhilosopher->philNum + 1]);
	}

	eatingBigMacs(thePhilosopher->philNum);

	pthread_mutex_unlock(&thePhilosopher->forks[thePhilosopher->philNum]);

	if(isLastPhilosopher(thePhilosopher))
	{
		pthread_mutex_unlock(&thePhilosopher->forks[0]);
	}
	else
	{
		pthread_mutex_unlock(&thePhilosopher->forks[thePhilosopher->philNum + 1]);
	}

	philosophizing(thePhilosopher->philNum);

	return(NULL);
}

int isLastPhilosopher(aPhil * thePhilosopher)
{
	if((thePhilosopher->philNum + 1) != (thePhilosopher->total))
	{
		return FALSE;
	}

	return TRUE;
}
aPhil * createPhilosopher(int philNum)
{
	int i;

	aPhil * new = malloc(sizeof(aPhil));
	new->total = philNum;
    new->threads = malloc(sizeof(pthread_t) * philNum);
    new->forks = malloc(sizeof(pthread_mutex_t) * philNum);
    for (i = 0; i < philNum; i++)
    {
	    philosophizing(i);
        pthread_mutex_init(&new->forks[i], NULL);
    }

    return new;
}
