#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#define NUM_THREADS 10
pthread_mutex_t mutex;
int resource = 5; //5 resources available, 0 means none
void *allocator(void *param);

int main(void)
{
	int i;
	pthread_t tids[NUM_THREADS];
	pthread_mutex_init(&mutex, NULL);
	for (i = 0; i < NUM_THREADS; i++)
	{
		pthread_create(&tids[i], NULL, allocator, i+1);
	}
	for (i = 0; i < NUM_THREADS; i++)
	{
		pthread_join(tids[i], NULL);
	}
	printf("*** Mutex Test Done ***\n");
	return 0;
}

void *allocator(void *param)
{ // sleep for a random period of time
	sleep((int)random()%10);
  // allocate a resource
	allocate_resource();
	if (resource == 0)
		printf("No resource is available for thread: %d\n", param);
	else
	{
		pthread_mutex_lock(&mutex);
		if (resource < 0)
		{
			fprintf(stderr,"***resource ALREADY IN USE****\n");
		}
		else
			fprintf(stderr,"***resource not in use****\n");
		pthread_mutex_unlock(&mutex);
		//sleep for a random period of time
		sleep((int)random()%10);
		//release the pid
		printf("Release the resource now, thread: %d\n", param);
		release_resource();
	}
	
}

void allocate_resource(void)
{
	//acquire the mutex lock
	if (pthread_mutex_lock(&mutex) != 0)
		fprintf(stderr,"Unable to acquire lock\n");
	else
	{
		fprintf(stderr,"Acquire the lock\n");
		if (resource != 0)
		{
			fprintf(stderr,"Resource available. Allocated the resource\n");
			resource--;
		}
		else
			fprintf(stderr,"Resource is in use\n");
	}
	if (pthread_mutex_unlock(&mutex) != 0)
		fprintf(stderr,"Unable to release mutex\n");
	else
		fprintf(stderr,"Release the mutex lock \n");
}

void release_resource(void)
{
	if (pthread_mutex_lock(&mutex) != 0)
		fprintf(stderr,"Unable to acquire mutex lock\n");
	else
	{
		fprintf(stderr,"Acquire the lock...now release the resource\n");
		resource++;
	}
	if (pthread_mutex_unlock(&mutex) != 0)
		fprintf(stderr,"Unable to release mutex lock\n");
}
