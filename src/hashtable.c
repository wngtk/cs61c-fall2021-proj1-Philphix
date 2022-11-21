#include "hashtable.h"

/*
 * General utility routines (including malloc()).
 */
#include <stdlib.h>

/*
 * Standard IO and file routines.
 */
#include <stdio.h>

/*
 * String utility routines.
 */
#include <string.h>

/*
 * This creates a new hash table of the specified size and with
 * the given hash function and comparison function.
 */
HashTable *createHashTable(int size, unsigned int (*hashFunction)(void *),
                           int (*equalFunction)(void *, void *)) {
  int i = 0;
  HashTable *newTable = malloc(sizeof(HashTable));
  if (NULL == newTable) {
    fprintf(stderr, "malloc failed \n");
    exit(1);
  }
  newTable->size = size;
  newTable->buckets = malloc(sizeof(struct HashBucketEntry *) * size);
  if (NULL == newTable->buckets) {
    fprintf(stderr, "malloc failed \n");
    exit(1);
  }
  for (i = 0; i < size; i++) {
    newTable->buckets[i] = NULL;
  }
  newTable->hashFunction = hashFunction;
  newTable->equalFunction = equalFunction;
  return newTable;
}

/* Task 1.2 */
void insertData(HashTable *table, void *key, void *data) {
  // -- TODO --
  // HINT:
  // 1. Find the right hash bucket location with table->hashFunction.
  // 2. Allocate a new hash bucket entry struct.
  // 3. Append to the linked list or create it if it does not yet exist. 
  unsigned int index = table->hashFunction(key) % table->size;
  HashBucketEntry *entry = malloc(sizeof(HashBucketEntry));
  HashBucketEntry **indirect = &table->buckets[index];

  if (entry == NULL) {
    fprintf(stderr, "malloc faild\n");
  }
  entry->data = data;
  entry->key = key;
  entry->next = NULL;

  while (*indirect != NULL) {
    indirect = &(*indirect)->next;
  }
  *indirect = entry;
}

/* Task 1.3 */
void *findData(HashTable *table, void *key) {
  // -- TODO --
  // HINT:
  // 1. Find the right hash bucket with table->hashFunction.
  // 2. Walk the linked list and check for equality with table->equalFunction.
  HashBucketEntry *bucket = table->buckets[table->hashFunction(key) % table->size];
  while (bucket != NULL && !table->equalFunction(bucket->key, key)) {
    bucket = bucket->next;
  }
  return bucket ? bucket->data : NULL;
}

/* Task 2.1 */
unsigned int stringHash(void *s) {
  // -- TODO --
  // fprintf(stderr, "need to implement stringHash\n");
  /* To suppress compiler warning until you implement this function, */
  unsigned int hashval = 0;
  char *str = s;
  while (*str) {
    hashval = hashval * 31 + *str;
    str++;
  }
  return hashval;
}

/* Task 2.2 */
int stringEquals(void *s1, void *s2) {
  // -- TODO --
  // fprintf(stderr, "You need to implement stringEquals");
  /* To suppress compiler warning until you implement this function */
  return !strcmp((char*)s1, (char*)s2);
}