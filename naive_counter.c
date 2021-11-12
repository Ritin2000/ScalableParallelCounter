// Names: Ashwin Haridas, Ritin Nair
// Netids: ah1058, rrn32
// iLab Used: kill.cs.rutgers.edu

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define COUNTER_VALUE (1UL << 24)

int count;
pthread_t* threads;
int thread_num;

void* increment(void* args)
{
	int i = 0;
	for (i = 0; i < COUNTER_VALUE; i++)
	{
		count++;
	}

	pthread_exit(NULL);
}

int main(int argc, char** argv) {

	// read amount of threads from command line
	if (argc != 2)
	{
		printf("Please enter a valid number of threads\n");
		exit(0);
	}
	else
	{
		thread_num = atoi(argv[1]);
		if (thread_num == 0)
		{
			printf("Cannot have 0 threads\n");
			exit(0);
		} 
	}

	// initialize global counter
	count = 0;

	// holds pthread_t values in an array
	threads = (pthread_t*)malloc(thread_num * sizeof(pthread_t));

	struct timeval end, start;
	gettimeofday(&start, NULL);
	// create threads with the increment function
	int i = 0;
	for (i = 0; i < thread_num; i++)
	{
		pthread_create(&threads[i], NULL, increment, NULL);
	}

	// wait for threads to finish executing
	for (i = 0; i < thread_num; i++)
	{
		pthread_join(threads[i], NULL);
	}
	
	gettimeofday(&end, NULL);
	double start_in_milli = (start.tv_sec) * 1000 + (start.tv_usec) / 1000;
	double end_in_milli = (end.tv_sec) * 1000 + (end.tv_usec) / 1000;
	double elapsed = end_in_milli - start_in_milli;
	printf("Counter finish in %f ms\n", elapsed);
	printf("The value of counter should be: %ld\n", thread_num * COUNTER_VALUE);
	printf("The value of counter is: %d\n", count);

	return 0;
}
