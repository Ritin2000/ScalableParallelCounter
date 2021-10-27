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

	clock_t begin = clock();
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
	clock_t end = clock();

	double runtime = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Counter finish in %f ms\n", runtime);
	printf("The value of counter should be: %ld\n", thread_num * COUNTER_VALUE);
	printf("The value of counter is: %d\n", count);

	return 0;
}
