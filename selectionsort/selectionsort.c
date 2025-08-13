#include <stdio.h>


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

void selection_sort(int arr[], size_t arr_size) {
	for(size_t i=0;i<arr_size - 1;i++) {
		int max = i;
		for(size_t j=i+1;j<arr_size;j++) {
			if(arr[j] > arr[max]) {
				max = j;
			}
		}
		swap(&arr[i], &arr[max]);
	}
}

int main() {
	int arr[] = {45, 40, 19, 32, 16, 21, 1, 3, 2};
	size_t arr_size = sizeof(arr) / sizeof(int);
	printf("Unsorted Array:\n");
	print_array(arr, arr_size);
	selection_sort(arr, arr_size);
	printf("Sorted Array:\n");
	print_array(arr, arr_size);
	return 0;
}
