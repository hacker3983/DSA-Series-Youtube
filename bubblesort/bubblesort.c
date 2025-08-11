#include <stdio.h>
#include <stdlib.h>

/*
 * Bubble Sort is a comparison based algorithm - It compares pairs of adjacent elements and
 * swaps them into the correct order until the array is sorted
 * Time Complexity - O(n^2)
 * Advantage:
 * 1. Easy to implement
 * 2. Best for small datasets
 * Disadvantage:
 * 1. Inefficient for large datasets
*/

void print_array(int arr[], size_t arr_size) {
	for(size_t i=0;i<arr_size;i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b, *b = temp;
}

void bubblesort(int arr[], size_t arr_size) {
	for(size_t i=0;i<arr_size;i++) {
		for(size_t j=0;j<arr_size - i - 1;j++) {
			if(arr[j] > arr[j+1]) {
				swap(&arr[j], &arr[j+1]);
			}
		}
	}
}

int main() {
	int arr[] = {9, 10, 7, 0, 8, 1, 2};
	size_t arr_size = sizeof(arr) / sizeof(int);
	printf("Unsorted Array:\n");
	print_array(arr, arr_size);
	printf("Sorted Array:\n");
	bubblesort(arr, arr_size);
	print_array(arr, arr_size);
	return 0;
}
