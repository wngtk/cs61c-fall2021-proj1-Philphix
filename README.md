# fa21-proj1-starter

<!-- Please add a description about what you created! Also add lessons you learned or bugs you encountered.  -->
The puzzle is readDictionary() and processInput(). The longest word is very long. So you must choose a way to handle words which length is thousands.

## Hashtable

Use hash algorithm in K&R.

## Task 1.2

A graceful implementation of insertData(). The while loop is clean.
Append data just one line code: `*indirect = entry;`.
This trick is learned from Linus Torvalds TED talk.

https://fengmuzi2003.gitbook.io/csapp3e/di-er-zhang-zhong-dian-jie-du
https://www.bilibili.com/video/BV1Cs411y7GQ/?from=search&seid=13695301827862285580

```c
/*
 * This header file defines an interface to a generic chained hash table. 
 * It stores void * data and uses two functions, int (*) (void *)
 * and int (*) (void *, void *), to compute the hash and check
 * for equality.
 */
typedef struct HashBucketEntry {
  void *key;
  void *data;
  struct HashBucketEntry *next;
} HashBucketEntry;

/* Task 1.1 */
typedef struct HashTable {
  // -- TODO --
  // HINT: Take a look at createHashTable.
  int size;
  HashBucketEntry **buckets;
  unsigned int (*hashFunction)(void *);
  int (*equalFunction)(void *, void *);
} HashTable;

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
```
