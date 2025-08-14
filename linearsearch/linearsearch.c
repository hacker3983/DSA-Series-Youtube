#include <stdio.h>

/*
 * Linear Search - A searching algorithm that searches through a list or collection one element at a time
 * Advantages:
 * It is fast on small to medium sized data sets
 * It is easy to implement
 * It is good for searching through data structures that don't allow random access such as linked lists
 * Disadvantage:
 * It is slow on large datasets
 * Time Complexity: O(n)
*/

int linearsearch(int arr[], int size, int target_value) {
	for(int i=0;i<size;i++) {
		if(arr[i] == target_value) {
			return i;
		}
	}
	return -1;
}


int main() {
	int arr[] = {10, 3, 7, 2, 1, 19, 12};
	int size = sizeof(arr) / sizeof(int);
	int target_value = 15;
	int found_index = linearsearch(arr, size, target_value);
	if(found_index != -1) {
		printf("Found the value %d at index %d\n", target_value, found_index);
	} else {
		printf("The value %d was not found in the array\n", target_value);
	}
	return 0;
}
