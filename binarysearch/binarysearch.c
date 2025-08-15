#include <stdio.h>
#include <stdlib.h>

/* Binary Search is a searching algorithm that finds the position of a target value in a sorted array
 * It does this by checking if the middle value is equal to the target value
 * If the middle value is less than the target value it searches the right half
 * If the middle value is greater than the target value it searches the left half
 * Advantages:
 * 1. Fast and Efficient
 * 2. Fewer comparisons compared to linear search
 * 3. It is easy to understand and implement
 *
 * Disadvantages:
 * 1. Only works on sorted arrays
 * 2. Not efficent on small data sets
 * 3. Harder to implement than linear search
 * 4. Only works with random access data structures like arrays
 *
 * Time Complexity:
 * O(log n)
*/
int binarysearch(int arr[], int size, int target_value) {
	int left = 0, right = size - 1;
	while(left <= right) {
		int mid = left + (right - left) / 2;
		if(arr[mid] == target_value) {
			return mid;
		} else if(arr[mid] < target_value) {
			left = mid + 1;
		} else if(arr[mid] > target_value) {
			right = mid - 1;
		}
	}
	return -1;
}

int main() {
	int arr[] = {3, 4, 9, 14, 17, 19, 21, 33, 39, 42};
	int size = sizeof(arr) / sizeof(int);
	int target_value = 55;
	int found_index = binarysearch(arr, size, target_value);
	if(found_index != -1) {
		printf("The target value %d was found at index %d\n", target_value, found_index);
	} else {
		printf("The target value %d is not in the array\n", target_value);
	}
	return 0;
}
