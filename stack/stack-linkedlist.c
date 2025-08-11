#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct linked_list {
	int value;
	struct linked_list* next;
} linked_list_t;

typedef struct stack {
	linked_list_t* linked_list;
} stack_t;

linked_list_t* linked_list_createnode(int value) {
	linked_list_t* new_node = malloc(sizeof(linked_list_t));
	new_node->value = value;
	new_node->next = NULL;
	return new_node;
}

void stack_init(stack_t* stack) {
	stack->linked_list = NULL;
}

void stack_push(stack_t* stack, int value) {
	linked_list_t* new_node = linked_list_createnode(value);
	new_node->next = stack->linked_list;
	stack->linked_list = new_node;
}

bool stack_pop(stack_t* stack, int* value) {
	if(!stack->linked_list) {
		return false;
	}
	*value = stack->linked_list->value;
	linked_list_t* next_node = stack->linked_list->next;
	free(stack->linked_list);
	stack->linked_list = next_node;
	return true;
}

bool stack_peek(stack_t stack, int *value) {
	if(!stack.linked_list) {
		return false;
	}
	*value = stack.linked_list->value;
	return true;
}

void stack_print(stack_t stack) {
	if(!stack.linked_list) {
		printf("Stack is Empty\n");
		return;
	}
	linked_list_t* linked_list = stack.linked_list;
	printf("The values in the stack are:\n");
	while(linked_list) {
		printf("%d\n", linked_list->value);
		linked_list = linked_list->next;
	}
}

void stack_destroy(stack_t* stack) {
	linked_list_t* linked_list = stack->linked_list;
	while(linked_list) {
		linked_list_t* current = linked_list;
		linked_list = current->next;
		free(current);
	}
}

void main() {
	stack_t stack = {0};
	stack_push(&stack, 1);
	stack_push(&stack, 2);
	stack_push(&stack, 3);
	stack_push(&stack, 4);
	int popped_value = 0, peeked_value = 0;
	while(stack.linked_list) {
		if(stack_peek(stack, &peeked_value)) {
			printf("The peeked value at the top of the stack is %d\n",
				peeked_value);
		}
		stack_print(stack);
		if(stack_pop(&stack, &popped_value)) {
			printf("Popped value off the stack: %d\n", popped_value);
		}
	}
	stack_print(stack);
	stack_destroy(&stack);
}
