#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct stack {
	int* arr;
	size_t size;
} stack_t;

void stack_init(stack_t* stack) {
	stack->arr = NULL;
	stack->size = 0;
}

void stack_push(stack_t* stack, int value) {
	size_t new_count = stack->size + 1;
	int* new_ptr = realloc(stack->arr, new_count * sizeof(int));
	if(!new_ptr) {
		return;
	}
	new_ptr[new_count-1] = value;
	stack->arr = new_ptr;
	stack->size = new_count;
}

bool stack_pop(stack_t* stack, int* value) {
	if(!stack->arr) {
		return false;
	}
	stack->size--;
	*value = stack->arr[stack->size];
	stack->arr = realloc(stack->arr, stack->size * sizeof(int));
	return true;
}

bool stack_peek(stack_t stack, int* value) {
	if(!stack.arr) {
		return false;
	}
	*value = stack.arr[stack.size-1];
	return true;
}

void stack_print(stack_t stack) {
	if(!stack.arr) {
		printf("Stack is Empty\n");
		return;
	}
	printf("Stack values are:\n");
	for(size_t i=stack.size-1;i>=0;) {
		printf("%d\n", stack.arr[i]);
		if(!i) {
			break;
		}
		i--;
	}
}

void stack_destroy(stack_t* stack) {
	free(stack->arr);
	stack_init(stack);
}

void main() {
	stack_t stack = {0};
	stack_push(&stack, 1);
	stack_push(&stack, 2);
	stack_push(&stack, 3);
	stack_push(&stack, 4);

	size_t old_size = stack.size;
	int popped_value = 0, peeked_value = 0;
	for(size_t i=0;i<old_size;i++) {
		if(stack_peek(stack, &peeked_value)) {
			printf("The peeked value is %d\n", peeked_value);
		}
		stack_print(stack);
		if(stack_pop(&stack, &popped_value)) {
			printf("Popped value off the stack: %d\n", popped_value);
		}
	}
	stack_print(stack);
	stack_destroy(&stack);
}
