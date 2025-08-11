#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct queue {
	int* arr;
	size_t size;
} queue_t;

void queue_init(queue_t* queue) {
	queue->arr = NULL;
	queue->size = 0;
}

void queue_enqueue(queue_t* queue, int value) {
	int* new_arr = realloc(queue->arr,
			(queue->size + 1) * sizeof(int));
	if(!new_arr) {
		return;
	}
	new_arr[queue->size] = value;
	queue->arr = new_arr;
	queue->size++;
}

bool queue_dequeue(queue_t* queue, int* value) {
	if(!queue->arr) {
		return false;
	}
	*value = queue->arr[0];
	for(size_t i=0;i<queue->size-1;i++) {
		int current_value = queue->arr[i];
		queue->arr[i] = queue->arr[i+1];
		queue->arr[i+1] = current_value;
	}
	queue->size--;
	if(!queue->size) {
		free(queue->arr);
		queue_init(queue);
		return true;
	}
	queue->arr = realloc(queue->arr, queue->size * sizeof(int));
	return true;
}

bool queue_peek(queue_t queue, int* value) {
	if(!queue.arr) {
		return false;
	}
	*value = queue.arr[0];
	return true;
}

void queue_print(queue_t queue) {
	if(!queue.arr) {
		printf("Queue is Empty\n");
		return;
	}
	printf("Queue values are:\n");
	for(size_t i=0;i<queue.size;i++) {
		printf("%d\n", queue.arr[i]);
	}
}

void queue_destroy(queue_t* queue) {
	free(queue->arr);
	queue_init(queue);
}

void main() {
	queue_t queue = {0};
	queue_enqueue(&queue, 1);
	queue_enqueue(&queue, 2);
	queue_enqueue(&queue, 3);
	queue_enqueue(&queue, 4);
	size_t old_size = queue.size;
	int dequeued_value = 0, peeked_value = 0;
	for(size_t i=0;i<old_size;i++) {
		if(queue_peek(queue, &peeked_value)) {
			printf("The peeked value is %d\n", peeked_value);
		}
		queue_print(queue);
		if(queue_dequeue(&queue, &dequeued_value)) {
			printf("Dequeued value %d\n", dequeued_value);
		}
	}
	queue_print(queue);
	queue_destroy(&queue);
}
