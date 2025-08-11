#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct dynamic_array {
	int* values;
	size_t count;
} dynamic_array_t;

void dynamic_array_init(dynamic_array_t* array) {
	array->values = NULL;
	array->count = 0;
}

void dynamic_array_append(dynamic_array_t* array, int value) {
	int* new_values = NULL;
	size_t new_count = array->count + 1;
	if(!array->values) {
		new_values = malloc(sizeof(int));
	} else {
		new_values = realloc(array->values,
				new_count * sizeof(int));
	}
	if(!new_values) {
		return;
	}
	new_values[new_count-1] = value;
	array->values = new_values;
	array->count = new_count;
}

void dynamic_array_print(dynamic_array_t array) {
	printf("[");
	for(size_t i=0;i<array.count;i++) {
		printf("%d", array.values[i]);
		if(i != array.count-1) {
			printf(", ");
		}
	}
	printf("]\n");
}

bool dynamic_array_findvalue(dynamic_array_t array,
int value, size_t* found_index) {
	bool found = false;
	for(size_t i=0;i<array.count;i++) {
		if(array.values[i] == value) {
			*found_index = i;
			found = true;
			break;
		}
	}
	return found;
}

bool dynamic_array_remove(dynamic_array_t* array, int value) {
	size_t value_index = 0;
	if(!dynamic_array_findvalue(*array, value, &value_index)) {
		return false;
	}
	for(size_t i=value_index;i<array->count-1;i++) {
		int current_value = array->values[i];
		array->values[i] = array->values[i+1];
		array->values[i+1] = current_value;
	}
	array->count--;
	if(!array->count) {
		free(array->values);
		dynamic_array_init(array);
		return true;
	}
	array->values = realloc(array->values,
		array->count * sizeof(int));
	return true;
}

void dynamic_array_destroy(dynamic_array_t* array) {
	free(array->values);
	dynamic_array_init(array);
}

void main() {
	dynamic_array_t array;
	dynamic_array_init(&array);
	for(size_t i=5;i<100;i+=5) {
		dynamic_array_append(&array, i);
	}
	dynamic_array_print(array);
	size_t found_index = 0;
	int target_values[] = {18, 45, 19, 15};
	size_t n = sizeof(target_values) / sizeof(int);
	for(size_t i=0;i<n;i++) {
		if(dynamic_array_findvalue(array, target_values[i], &found_index)) {
			printf("Found value %d the array at index %zu\n",
				target_values[i], found_index);
		} else {
			printf("The value %d doesn't exist inside the array\n",
				target_values[i]);
		}
	}
	int removal_values[] = {10, 19, 45, 68, 19, 65};
	size_t removal_count = sizeof(removal_values) / sizeof(int);
	for(size_t i=0;i<removal_count;i++) {
		if(dynamic_array_remove(&array, removal_values[i])) {
			printf("Successfully removed value %d!\n", removal_values[i]);
		} else {
			printf("Removing value %d was unsuccessful!\n", removal_values[i]);
		}
	}
	dynamic_array_print(array);
	dynamic_array_destroy(&array);
}
