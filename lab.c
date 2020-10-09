/**
 * Name: Jane Doe
 * Email: janedoe@u.boisestate.edu
 * Github Username: jdoe
 */
#include "lab.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>

/*
 * insertion_sort(int A[], int p, int r):
 *
 * description: Sort the section of the array A[p..r].
 */
void insertion_sort(int A[], int p, int r)
{
	int j;

	for (j=p+1; j<=r; j++) {
		int key = A[j];
		int i = j-1;
		while ((i > p-1) && (A[i] > key)) {
			A[i+1] = A[i];
			i--;
		}
		A[i+1] = key;
	}
}
/*
 *mergesort(int A[], int p, int r):
 *
 *description: andles the sorting of each processes portion of the array
 */
void mergesort(int A[], int p, int r){
	if(r-p+1 <= INSERTION_SORT_THRESHOLD)  {
			insertion_sort(A,p,r);
	} else {
		int q =  p + (r - p)/2;
		if(p < r){
			mergesort(A, p, q);
			mergesort(A, q+1, r);
			merge(A, p, q, r);
		}
	}	
} 

/*
 * serial_mergesort(void* inupt):
 *
 * description: distributes each process its own portion of the array to sort
 */
void* serial_mergesort(void *input)
{
	struct args *param = (struct args*) input; 
	
	mergesort(param->A, param->p, param->r);
	
	pthread_exit(NULL);
}

/*
 * merge(int A[], int p, int q, int r):
 *
 * description: Merge two sorted sequences A[p..q] and A[q+1..r]
 *              and place merged output back in array A. Uses extra
 *              space proportional to A[p..r].
 */
void merge(int A[], int p, int q, int r)
{
		int *B = (int *) malloc(sizeof(int) * (r-p+1));

	int i = p;
	int j = q+1;
	int k = 0;
	int l;
	
	while ((i <= q) && (j <= r)) {
		if (A[i] < A[j]) {
			B[k] = A[i];
			i++;
		} else {
			B[k] = A[j];
			j++;
		}
		k++;
	}

	if (i <= q) {
		for (l=i; l<=q; l++) {
			B[k] = A[l];
			k++;
		}
	} else {
		for (l=j; l<=r; l++) {
			B[k] = A[l];
			k++;
		}
	}
	
	k=0;
	for (l=p; l<=r; l++) {
		A[l] = B[k];
		k++;
	}

	free(B); 														
}
