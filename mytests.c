#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/times.h> /* for times system call */
#include <sys/time.h>  /* for gettimeofday system call */
#include <unistd.h>
#include <pthread.h>
#include <error.h>
#include "lab.h"

// function prototypes
int check_if_sorted(int A[], int n);
void generate_random_array(int A[], int n, int seed);
void* serial_mergesort(void* input);
void merge(int A[], int p, int q, int r);
void insertion_sort(int A[], int p, int r);
double getMilliSeconds(void);


/*
---------------------------------------------------------------------------
clock_t times(struct tms *buffer);
times() fills the structure pointed to by buffer with
time-accounting information.  The structure defined in
<sys/times.h> is as follows:
struct tms {
    clock_t tms_utime;       user time
    clock_t tms_stime;       system time
    clock_t tms_cutime;      user time, children
    clock_t tms_cstime;      system time, children
The time is given in units of 1/CLK_TCK seconds where the
value of CLK_TCK can be determined using the sysconf() function
with the agrgument _SC_CLK_TCK.
---------------------------------------------------------------------------
*/


float report_cpu_time(void)
{
	struct tms buffer;
	float cputime;

	times(&buffer);
	cputime = (buffer.tms_utime)/ (float) sysconf(_SC_CLK_TCK);
	return (cputime);
}


float report_sys_time(void)
{
	struct tms buffer;
	float systime;

	times(&buffer);
	systime = (buffer.tms_stime)/ (float) sysconf(_SC_CLK_TCK);
	return (systime);
}

double getMilliSeconds(void)
{
    struct timeval now;
    gettimeofday(&now, (struct timezone *)0);
    return (double) now.tv_sec*1000.0 + now.tv_usec/1000.0;
}


/*
 * generate_random_array(int A[], int n, int seed):
 *
 * description: Generate random integers in the range [0,RANGE]
 *              and store in A[1..n]
 */

#define RANGE 1000000

void generate_random_array(int A[], int n, int seed)
{
    int i;

	srandom(seed);
    for (i=1; i<=n; i++){
        A[i] = random()%RANGE;
    }
}


/*
 * check_if_sorted(int A[], int n):
 *
 * description: returns TRUE if A[1..n] are sorted in nondecreasing order
 *              otherwise returns FALSE
 */

int check_if_sorted(int A[], int n)
{
	int i=0;

	for (i=1; i<n; i++) {
		if (A[i] > A[i+1]) {
			return FALSE;
		}
	}
	return TRUE;
}




int main(int argc, char **argv) {

	if (argc < 3) { // there must be at least one command-line argument
			fprintf(stderr, "Usage: %s <input size> <num threads> [<seed>] \n", argv[0]);
			exit(1);
	}

	int n = atoi(argv[1]);
	int THREAD_MAX = atoi(argv[2]);
	int seed = 1;
	if (argc == 4)
		seed = atoi(argv[3]);

	//portion of the array that will be handled by each process
	//remainder is if the number of processes doesn't divide the problem evenly
	int partition = n / THREAD_MAX, remainder = n % THREAD_MAX, i = 0;

	int *A = (int *) malloc(sizeof(int) * (n + 1));
	
	//a struct of parameters for each process
	//contains array A, p, and r
        struct args * params = malloc(THREAD_MAX * sizeof(struct args));
	for(i = 0; i < THREAD_MAX; i++){
        	params[i].A = A;
	}

        generate_random_array(A,n, seed);
	
	double start_time;
	double sorting_time;

	// sort the input (and time it)
	start_time = getMilliSeconds();
	pthread_t threads[THREAD_MAX];
	
	//create threads
	for(i = 0; i < THREAD_MAX; i++){
		params[i].p = (partition * i) + 1;
		params[i].r = params[i].p + partition - 1;
		if(i == THREAD_MAX - 1) params[i].r += remainder;	
			
		pthread_create(&threads[i], NULL, serial_mergesort, &params[i]);
	}

	//join threads
	for(i = 0; i < THREAD_MAX; i++){
		pthread_join(threads[i], NULL);
	}
	
	//merge the result from each process
	struct args *temp = &params[0];
	for(i = 1; i < THREAD_MAX; i++){
		merge(A, temp->p, params[i].p - 1 , params[i].r);
	}
	sorting_time = getMilliSeconds() - start_time;

	// print results if correctly sorted otherwise cry foul and exit
	if (check_if_sorted(A,n)) {
		printf("Sorting %d elements took %4.2lf seconds.\n", n,  sorting_time/1000.0);
	} else {
		printf("%s: sorting failed!!!!\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	free(params);
	free(A);
	exit(EXIT_SUCCESS);
	
	return 0;
}
