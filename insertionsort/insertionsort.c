#include <stdio.h>

/*
 * Insertion sort - compares elements to the left
 *                  shift elements to the right to create space to insert a value
 *                  
 *                  Quadratic time O(n^2)
 *                  small data set = Ok!
 *                  large data set = Poor!
 *
 *                  less steps than Bubble Sort
 *                  Best case is O(n) compared to Selection Sort O(n^2)
*/
void print_array(int arr[], size_t size) {
	for(size_t i=0;i<size;i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void insertionsort(int arr[], size_t size) {
	for(size_t i=1;i<size;i++) {
		int current = arr[i];
		size_t j = i;
		while(j > 0 && arr[j - 1] > current) {
			arr[j] = arr[j - 1];
			j--;
		}
		arr[j] = current;
	}
}

int main() {
	int arr[] = {9, 5, 3, 1, 4, 12, 10, 7, 6, 8};
	size_t size = sizeof(arr) / sizeof(int);
	printf("Unsorted Array:\n");
	print_array(arr, size);
	insertionsort(arr, size);
	printf("Sorted Array:\n");
	print_array(arr, size);
	return 0;
}
