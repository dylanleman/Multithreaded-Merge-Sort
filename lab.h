#ifndef __LAB_H
#define __LAB_H

#ifdef __cplusplus
extern "C" {
#endif

#define TRUE 1
#define FALSE 0

// function prototypes
void* serial_mergesort(void *input);
void merge(int A[], int p, int q, int r);
void insertion_sort(int A[], int p, int r);
void mergesort(int A[], int p, int r);

//args struct
struct args{
	int p;
	int r;
	int *A;
};

const int INSERTION_SORT_THRESHOLD = 100; //based on trial and error

#ifdef __cplusplus
}
#endif
#endif //__LAB_H
