#include <stdio.h>
#include <stdlib.h>

typedef struct linked_list {
	int value;
	struct linked_list* next;
} linked_list_t;

linked_list_t* linked_list_createnode(int value) {
	linked_list_t* new_node = malloc(sizeof(linked_list_t));
	new_node->value = value;
	new_node->next = NULL;
	return new_node;
}

void linked_list_insertfront(linked_list_t** head, int value) {
	linked_list_t* new_node = linked_list_createnode(value);
	new_node->next = *head;
	*head = new_node;
}

void linked_list_pushback(linked_list_t** head, int value) {
	linked_list_t* new_node = linked_list_createnode(value),
		*ref = *head;
	if(!ref) {
		*head = new_node;
		return;
	}
	while(ref->next) {
		ref = ref->next;
	}
	ref->next = new_node;
}

void linked_list_remove(linked_list_t** head, int value) {
	linked_list_t* ref = *head,
		*next_node = NULL,
		*target = NULL;
	if(ref && ref->value == value) {
		next_node = ref->next;
		free(ref);
		*head = next_node;
		return;
	}
	while(ref->next) {
		if(ref->next->value == value) {
			target = ref->next;
			break;
		}
		ref = ref->next;
	}
	if(!target) {
		return;
	}
	next_node = target->next;
	free(target);
	ref->next = next_node;
}

void linked_list_print(linked_list_t* head) {
	while(head) {
		printf("%d", head->value);
		if(head->next) {
			printf(" -> ");
		}
		head = head->next;
	}
	printf("\n");
}

void linked_list_destroy(linked_list_t** head) {
	linked_list_t* ref = *head;
	while(ref) {
		linked_list_t* next_node = ref->next;
		free(ref);
		ref = next_node;
	}
}

void main() {
	linked_list_t* l1 = NULL, *l2 = NULL;

	// linked list 1 pushback	
	linked_list_pushback(&l1, 2);
	linked_list_pushback(&l1, 4);
	linked_list_pushback(&l1, 6);
	linked_list_pushback(&l1, 8);
	linked_list_pushback(&l1, 10);

	// linked list 2 insertfront
	linked_list_insertfront(&l2, 2);
	linked_list_insertfront(&l2, 4);
	linked_list_insertfront(&l2, 6);
	linked_list_insertfront(&l2, 8);
	linked_list_insertfront(&l2, 10);

	printf("Linked list 1 pushback:\n");
	linked_list_print(l1);

	printf("Linked list 2 insertfront:\n");
	linked_list_print(l2);

	int removal_list[] = {6, 4, 7, 10};
	size_t removal_count = sizeof(removal_list) / sizeof(int);
	for(size_t i=0;i<removal_count;i++) {
		printf("Removing %d from linked list 1\n", removal_list[i]);
		linked_list_remove(&l1, removal_list[i]);
	}
	printf("Linked list 1 after removing values\n");
	linked_list_print(l1);
	for(size_t i=0;i<removal_count;i++) {
		printf("Removing %d from linked list 2\n", removal_list[i]);
		linked_list_remove(&l2, removal_list[i]);
	}
	printf("Linked list 2 after removing values\n");
	linked_list_print(l2);
	linked_list_destroy(&l1);
	linked_list_destroy(&l2);
}
