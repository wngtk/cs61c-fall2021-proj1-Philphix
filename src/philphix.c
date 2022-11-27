/*
 * Include the provided hash table library.
 */
#include "hashtable.h"

/*
 * Include the header file.
 */
#include "philphix.h"

/*
 * Standard IO and file routines.
 */
#include <stdio.h>

/*
 * General utility routines (including malloc()).
 */
#include <stdlib.h>

/*
 * Character utility routines.
 */
#include <ctype.h>

/*
 * String utility routines.
 */
#include <string.h>

/*
 * This hash table stores the dictionary.
 */
HashTable *dictionary;

/*
 * The MAIN routine.  You can safely print debugging information
 * to standard error (stderr) as shown and it will be ignored in 
 * the grading process.
 */
#ifndef _PHILPHIX_UNITTEST
int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Specify a dictionary\n");
    return 1;
  }
  /*
   * Allocate a hash table to store the dictionary.
   */
  fprintf(stderr, "Creating hashtable\n");
  dictionary = createHashTable(0x61C, &stringHash, &stringEquals);

  fprintf(stderr, "Loading dictionary %s\n", argv[1]);
  readDictionary(argv[1]);
  fprintf(stderr, "Dictionary loaded\n");

  fprintf(stderr, "Processing stdin\n");
  processInput();

  /*
   * The MAIN function in C should always return 0 as a way of telling
   * whatever program invoked this that everything went OK.
   */
  return 0;
}
#endif /* _PHILPHIX_UNITTEST */

/* Task 3 */
void readDictionary(char *dictName) {
  // -- TODO --
  // fprintf(stderr, "You need to implement readDictionary\n");
  FILE *fp = fopen(dictName, "r");
  if (fp == NULL) {
    perror(dictName);
    exit(61);
  }

  char buffer[1024];
  char key[1024], data[1024];
  char *rv = NULL;
  while ((rv = fgets(buffer, sizeof(buffer), fp)) != NULL) {
    sscanf(rv, "%s %s", key, data);
    insertData(dictionary, strdup(key), strdup(data));
  }
}

void transform(char *data, int (*func)(int)) {
  while (*data) {
    *data = func(*data);
    data++;
  }
}

/* Task 4 */
void processInput() {
  // -- TODO --
  fprintf(stderr, "You need to implement processInput\n");
  char word[1024], data[1024], *exact, *lower, *mock_capitalized;
  char ch;
  int len = 0;

  while ((ch = getchar()) != EOF) {
    if (isalnum(ch) == 0) {
      word[len] = '\0';
      len = 0;
      strcpy(data, word);
      // Excat word
      exact = findData(dictionary, data);
      // Mock Capitalized
      transform(word+1, tolower);
      mock_capitalized = findData(dictionary, word);
      // Lower Case
      word[0] = tolower(word[0]);
      lower = findData(dictionary, word);
      if (exact) {
        printf("%s", exact);
      } else if (mock_capitalized) {
        printf("%s", mock_capitalized);
      } else if (lower) {
        printf("%s", lower);
      } else {
        printf("%s", data);
      }
      putchar(ch);
    } else {
      // Read the character from stdin. Save it into WORD.
      word[len++] = (char)ch;
    }
  }
}
