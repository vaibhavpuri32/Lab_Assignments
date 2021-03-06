/*
**  PROGRAM: Quick sort
**
**  PURPOSE: This is a program to sort an array using the Quick sort algorithm.
**           Quick sort sorts an array by picking the last element as a pivot element. The pivot element is placed correctly in the array.
**           Elements smaller than the pivot are placed to the left of it, and elements greater than it to the right.
**           Then, we recurse on the left and right subarrays to the pivot by calling the algorithm on them, until size of array is 1.
**
**			 If the array is initially:
**                5,1,3,4,2
**           We select the element 2 as pivot. After swapping, the array should look like:
**				  1,2,5,3,4
**           and the algorithm is called on the arrays [1] and [5,3,4].
**
**  USAGE:   Run the program and enter an integer in the command line when prompted. Random values are taken as elements for the array with size being the integer entered.
**
**  HISTORY: Written by Bharath Adikar, Aug 2019
*/
#include <omp.h>
#include <stdio.h> 
#include <stdlib.h>

#define lld long long int

// A utility function to swap two elements 
void swap(lld* a, lld* b) 
{ 
	lld t = *a; 
	*a = *b; 
	*b = t; 
} 

// Utility function to prnt all elements of array
void printArray(lld arr[], lld size) 
{ 
	lld i; 
	for (i=0; i < size; i++) 
		printf("%lld ",arr[i]); 
	printf("\n"); 
} 

/* This function takes last element as pivot, places 
the pivot element at its correct position in sorted 
	array, and places all smaller (smaller than pivot) 
to left of pivot and all greater elements to right 
of pivot */
lld partition (lld arr[], lld low, lld high) 
{ 
	lld pivot = arr[high]; // pivot 
	lld i = (low - 1); // Index of smaller element 

	for (lld j = low; j <= high- 1; j++) 
	{ 
		// If current element is smaller than the pivot 
		if (arr[j] < pivot) 
		{ 
			i++; // increment index of smaller element 
			swap(&arr[i], &arr[j]); 
		} 
	} 
	swap(&arr[i + 1], &arr[high]); 
	return (i + 1); 
} 

// Serial implementation of quicksort
void quickSort(lld arr[], lld low, lld high) 
{ 
	if (low < high) 
	{
		// pi is partitioning index, arr[p] is now at right place
		lld pi = partition(arr, low, high);

		// Separately sort elements before partition
		quickSort(arr, low, pi - 1);

		// Separately sort elements after partition
		quickSort(arr, pi + 1, high); 
	} 
} 

// Parallelised version of quicksort by using data sharing and taskwait constructs
void quickSortP(lld arr[], lld low, lld high) 
{ 
	if (low < high) 
	{ 
		lld pi;
		#pragma omp task shared(pi)
		pi = partition(arr, low, high); 

		#pragma omp taskwait
		quickSortP(arr, low, pi - 1); 

		#pragma omp taskwait
		quickSortP(arr, pi + 1, high); 
	} 
} 

// Function to check correctness of output
lld check_correctness(lld arr[], lld n){
	lld i,error=0;
	for(i=0;i<n-1;++i){
		if(arr[i+1]<arr[i])
			++error;
	}
	return error;
}

int main() 
{ 
	double start_time,time_taken;
	lld i,n,input,error;
	printf("Enter array size: ");
	scanf("%lld",&n);
	lld arr[n],arr2[n];

	for(i=0;i<n;++i){
		input = rand()%1003;
		arr[i] = input;
		arr2[i] = input;
	}

	// Serial quicksort
	start_time = omp_get_wtime();
	quickSort(arr, 0, n-1); 
	time_taken = omp_get_wtime()-start_time;
	error = check_correctness(arr,n);

	//printf("Sorted array: \n"); 
	//printArray(arr, n); 
	printf("Time taken for serial approach is %lf s\n",time_taken);
	if(error)
		printf("Error obtained: %lld\n",error);
	else
		printf("The output obtained is correct and has no errors.\n");
	printf("\n");

	// Parallel quicksort with taskwait directives
	start_time = omp_get_wtime(); 
	quickSortP(arr2, 0, n-1); 
	time_taken = omp_get_wtime()-start_time;
	error = check_correctness(arr2,n);

	//printf("Sorted array: \n"); 
	//printArray(arr2, n); 
	printf("Time taken for parallel approach is %lf s\n",time_taken);
	if(error)
		printf("Error obtained: %lld\n",error);
	else
		printf("The output obtained is correct and has no errors.\n");
	printf("\n");

	return 0; 
} 
