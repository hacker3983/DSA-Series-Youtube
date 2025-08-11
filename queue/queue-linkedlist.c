#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct linkedlist {
	int value;
	struct linkedlist *next, *tail;
} linked_list_t;

typedef struct queue {
	linked_list_t* linked_list;
} queue_t;

linked_list_t* linked_list_createnode(int value) {
	linked_list_t* new_node = malloc(sizeof(int));
	new_node->value = value;
	new_node->tail = new_node;
	new_node->next = NULL;
	return new_node;
}

void queue_init(queue_t* queue) {
	queue->linked_list = NULL;
}

void queue_enqueue(queue_t* queue, int value) {
	linked_list_t* new_node = linked_list_createnode(value);
	if(!queue->linked_list) {
		queue->linked_list = new_node;
		return;
	}
	queue->linked_list->tail->next = new_node;
	queue->linked_list->tail = new_node;
}

bool queue_dequeue(queue_t* queue, int* value) {
	if(!queue->linked_list) {
		return false;
	}
	linked_list_t* linked_list = queue->linked_list,
		*next_node = linked_list->next;
	*value = linked_list->value;
	if(next_node) {
		next_node->tail = linked_list->tail;
	}
	free(linked_list);
	queue->linked_list = next_node;
	return true;
}

bool queue_peek(queue_t queue, int* value) {
	if(!queue.linked_list) {
		return false;
	}
	*value = queue.linked_list->value;
	return true;
}

void queue_print(queue_t queue) {
	 linked_list_t* linked_list = queue.linked_list;
	 if(!linked_list) {
	 	printf("Queue is Empty\n");
		return;
	 }
	 printf("Queue values are:\n");
	 while(linked_list) {
		 printf("%d\n", linked_list->value);
		 linked_list = linked_list->next;
	 }
}

void queue_destroy(queue_t* queue) {
	linked_list_t* linked_list = queue->linked_list;
	while(linked_list) {
		linked_list_t* next_node = linked_list->next;
		free(linked_list);
		linked_list = next_node;
	}
	queue_init(queue);
}

void main() {
	queue_t queue = {0};
	queue_enqueue(&queue, 1);
	queue_enqueue(&queue, 2);
	queue_enqueue(&queue, 3);
	queue_enqueue(&queue, 4);
	int dequeued_value = 0, peeked_value = 0;
	while(queue.linked_list) {
		if(queue_peek(queue, &peeked_value)) {
			printf("The peeked value is %d\n", peeked_value);
		}
		queue_print(queue);
		if(queue_dequeue(&queue, &dequeued_value)) {
			printf("The dequeued value is %d\n", dequeued_value);
		}
	}
	queue_print(queue);
	queue_destroy(&queue);
}
