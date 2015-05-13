#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>

typedef struct {
    int     secs;
    int     usecs;
} TIME_DIFF;

TIME_DIFF * my_difftime (struct timeval *, struct timeval *);
void task(int);
void *thread_task(void *);
void serial(int);
void parallel(int);
void print_usage(int, char **);


int main(int argc, char *argv[]) {

	if (argc != 3) {print_usage(argc, argv);}

	int num_tasks = atoi(argv[2]);

	if (!strcmp(argv[1], "serial")) {
		serial(num_tasks);
	}
	else if (!strcmp(argv[1], "parallel")) {
		parallel(num_tasks);
	}
	else {
		print_usage(argc, argv);
	}

	printf("Main completed\n");
	pthread_exit(NULL);
}


void serial(int num_tasks)
{
	int i;
	clock_t start, end;
	double cpu_time_used;
	struct timeval mySt, myEnd;
	TIME_DIFF *diff;

  
	start = clock();
	gettimeofday(&mySt,NULL);


	/* Add your codes here. Hint: execute tasks serially */



    

	gettimeofday(&myEnd,NULL);
  
	diff = my_difftime (&mySt, &myEnd);
	printf ("Serial execution time is: %3d.%6d secs.\n", diff->secs, diff->usecs);
}


void parallel(int num_tasks)
{
	int num_threads = num_tasks;
	pthread_t thread[num_threads];
	int rc;
	long t;
	clock_t start, end;
	double cpu_time_used;
	struct timeval mySt, myEnd;
	TIME_DIFF *diff;

	gettimeofday(&mySt,NULL);

    /* Add your codes here. Hint: execute tasks in parallel by using "pthread_create" and "pthread_join" functions.*/








	gettimeofday(&myEnd,NULL);

	diff = my_difftime (&mySt, &myEnd);
	printf ("Parallel execution time is: %3d.%6d secs.\n", diff->secs, diff->usecs);
}

void print_usage(int argc, char *argv[])
{
	printf("Usage: %s serial|parallel num_tasks\n", argv[0]);
	exit(1);
}


TIME_DIFF * my_difftime (struct timeval * start, struct timeval * end)
{
    TIME_DIFF * diff = (TIME_DIFF *) malloc ( sizeof (TIME_DIFF) );
 
    if (start->tv_sec == end->tv_sec) {
        diff->secs = 0;
        diff->usecs = end->tv_usec - start->tv_usec;
    }
    else {
        diff->usecs = 1000000 - start->tv_usec;
        diff->secs = end->tv_sec - (start->tv_sec + 1);
        diff->usecs += end->tv_usec;
        if (diff->usecs >= 1000000) {
            diff->usecs -= 1000000;
            diff->secs += 1;
        }
    }
     
    return diff;
}


void task(int id)
{
	int i;
	double result = 0.0;
	printf("Task %d started\n", id);

	for (i = 0; i < 1000000; i++) {
		result = result + sin(i) * tan(i);
	}
	printf("Task %d completed with result %e\n", id, result);
}


void *thread_task(void *t)
{
	long id = (long) t;
	printf("Thread %ld started\n", id);
	task(id);
	printf("Thread %ld done\n", id);
	pthread_exit(0);
}





