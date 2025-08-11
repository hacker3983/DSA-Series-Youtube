#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct bucket {
	char* key;
	int value;
	struct bucket* next;
} bucket_t;

typedef struct hashtable {
	bucket_t** buckets;
	size_t size;
} hashtable_t;

bucket_t* hash_bucket_create(const char* key, int value) {
	bucket_t* new_bucket = malloc(sizeof(bucket_t));
	new_bucket->key = strdup(key);
	new_bucket->value = value;
	new_bucket->next = NULL;
	return new_bucket;
}

hashtable_t hashtable_create(size_t capacity) {
	hashtable_t new_hashtable = {0};
	new_hashtable.buckets = calloc(capacity, sizeof(bucket_t*));
	new_hashtable.size = capacity;
	return new_hashtable;
}

size_t hashtable_hash(hashtable_t hashtable, const char* key) {
	size_t hash_code = 0;
	for(size_t i=0;i<strlen(key);i++) {
		hash_code += key[i] * key[i];
	}
	hash_code %= hashtable.size;
	return hash_code;
}

bool hashtable_add(hashtable_t* hashtable, const char* key, int value) {
	size_t hash_code = hashtable_hash(*hashtable, key);
	bucket_t* bucket = hashtable->buckets[hash_code],
		*new_bucket = hash_bucket_create(key, value);
	if(!new_bucket) {
		return false;
	}
	if(!bucket) {
		hashtable->buckets[hash_code] = new_bucket;
		return true;
	}
	new_bucket->next = bucket;
	hashtable->buckets[hash_code] = new_bucket;
	return true;
}

bool hashtable_delete(hashtable_t* hashtable, const char* key) {
	size_t hash_code = hashtable_hash(*hashtable, key);
	bucket_t* bucket = hashtable->buckets[hash_code];
	if(!bucket) {
		return false;
	}
	bucket_t* next_bucket = bucket->next;
	if(strcmp(bucket->key, key) == 0) {
		free(bucket->key);
		free(bucket);
		hashtable->buckets[hash_code] = next_bucket;
		return true;
	}
	bucket_t* target = NULL;
	while(bucket->next) {
		if(strcmp(next_bucket->key, key) == 0) {
			target = next_bucket;
			break;
		}
		next_bucket = next_bucket->next;
		bucket = bucket->next;
	}
	if(!target) {
		return false;
	}
	next_bucket = target->next;
	free(target->key);
	free(target);
	bucket->next = next_bucket;
	return true;
}

bucket_t* hashtable_get(hashtable_t* hashtable, const char* key) {
	size_t hash_code = hashtable_hash(*hashtable, key);
	bucket_t* result = hashtable->buckets[hash_code];
	while(result) {
		if(strcmp(result->key, key) == 0) {
			break;
		}
		result = result->next;
	}
	return result;
}

void hashtable_print(hashtable_t hashtable) {
	if(!hashtable.buckets) {
		printf("The hashtable is empty\n");
		return;
	}
	for(size_t i=0;i<hashtable.size;i++) {
		printf("%zu: ", i);
		bucket_t* bucket = hashtable.buckets[i];
		if(!bucket) {
			printf("NULL\n");
		}
		while(bucket) {
			printf("Key: %s, Value: %d", bucket->key, bucket->value);
			if(bucket->next) {
				printf(", ");
			} else {
				printf("\n");
			}
			bucket = bucket->next;
		}
	}
}

void hashtable_destroy(hashtable_t* hashtable) {
	for(size_t i=0;i<hashtable->size;i++) {
		bucket_t* bucket = hashtable->buckets[i];
		while(bucket) {
			bucket_t* next_bucket = bucket->next;
			free(bucket->key);
			free(bucket);
			bucket = next_bucket;
		}
	}
	free(hashtable->buckets);
	hashtable->buckets = NULL;
	hashtable->size = 0;
}

int main() {
	hashtable_t persons = hashtable_create(10);
	printf("Hashtable:\n");
	hashtable_add(&persons, "John", 27);
	hashtable_add(&persons, "Tim", 19);
	hashtable_add(&persons, "Alice", 17);
	hashtable_add(&persons, "Kyle", 18);
	hashtable_add(&persons, "Alex", 21);
	hashtable_add(&persons, "William", 22);
	hashtable_print(persons);
	printf("The hashcode for Tim is %zu\n", hashtable_hash(persons, "Tim"));
	printf("The hashcode for Alice is %zu\n", hashtable_hash(persons, "Alice"));

		
	bucket_t* result = hashtable_get(&persons, "Bob");
	if(!result) {
		printf("The key doesn't exist within the hashtable\n");
	} else {
		printf("Got the result: %s -> %d\n", result->key, result->value);
	}

	result = hashtable_get(&persons, "Kyle");
	if(!result) {
		printf("The key doesn't exist within the hashtable\n");
	} else {
		printf("Got the result: %s -> %d\n", result->key, result->value);
	}
	hashtable_delete(&persons, "Tim");
	hashtable_delete(&persons, "Bob");	
	hashtable_delete(&persons, "Peter");
	hashtable_delete(&persons, "William");
	printf("The hashtable after deleting keys:\n");
	hashtable_print(persons);
	return 0;
}
