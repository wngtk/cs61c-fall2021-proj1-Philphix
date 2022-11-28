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

int getWord(FILE *fp, char *buf) {
  int len = 0;
  char ch;

  while (isspace(ch = fgetc(fp)))
    ;

  if (ch != EOF)
    buf[len++] = ch;

  while (isgraph(ch = fgetc(fp)))
    buf[len++] = ch;

  buf[len] = '\0';
  return len;
}

int get_word(FILE *fp, char **buf) {
  int len = 0;
  char c;

  *buf = malloc(len + 1);

  while (isspace(c = fgetc(fp)))
    ;

  if (c != EOF) {
    (*buf)[len++] = c;
    *buf = realloc(*buf, len + 1);
  }

  while (isgraph(c = fgetc(fp))) {
    (*buf)[len++] = c;
    *buf = realloc(*buf, len + 1);
  }
  (*buf)[len] = '\0';
  return len;
}

/* Task 3 */
void readDictionary(char *dictName) {
  // -- TODO --
  // fprintf(stderr, "You need to implement readDictionary\n");
  FILE *fp = fopen(dictName, "r");
  if (fp == NULL) {
    perror(dictName);
    exit(61);
  }

  char *key, *data;
  char *buffer;
  int keyLen, dataLen;

  while ((keyLen = get_word(fp, &buffer)) != 0) {
    key = strcpy(malloc(keyLen), buffer);
    dataLen = get_word(fp, &buffer);
    data = strcpy(malloc(dataLen), buffer);
    insertData(dictionary, key, data);
  }
}

void transform(char *data, int (*func)(int)) {
  while (*data) {
    *data = func(*data);
    data++;
  }
}

int readWord(FILE *stream, char **word) {
  int c;
  int len = 0;

  *word = malloc(len + 1);

  c = fgetc(stream);
  if (!isalnum(c)) {
    return c;
  }

  (*word)[len++] = c;
  *word = realloc(*word, len + 1);

  while ( 1 ) {
    (*word)[len] = fgetc(stream);
    if (!isalnum((*word)[len])) {
      ungetc((*word)[len], stream);
      break;
    }
    len++;
    *word = realloc(*word, len + 1);
  }
  (*word)[len] = '\0';
  return (*word)[0];
}

#define MAXWORD 100

int read_word(char *, int, FILE *);
/* Rivised from K&R getword: get next word or character from input */
int read_word(char *word, int lim, FILE *stream) {
  int c;
  char *w = word;

  c = fgetc(stream);
  if (!isalnum(c)) {
    return c;
  }

  *w++ = c;
  for (; --lim > 0; w++) {
    *w = fgetc(stream);
    if (!isalnum(*w)) {
      ungetc(*w, stream);
      break;
    }
  }

  *w = '\0';
  return word[0];
}

char* identity(char *w)
{
  return w;
}

char* lower(char *w)
{
  char *s = w;
  while (*s) {
    *s = tolower(*s);
    s++;
  }
  return w;
}

char* lowerExceptFirst(char *w)
{
  lower(w+1);
  return w;
}

/* Task 4 */
void processInput() {
  // -- TODO --
  // fprintf(stderr, "You need to implement processInput\n");
  int i;
  // char word[MAXWORD], back[MAXWORD];
  char rv;
  char *word, *back;
  char* (*variations[])(char*) = {
    identity,
    lowerExceptFirst,
    lower,
  };

  // while ((rv = read_word(word, MAXWORD, stdin)) != EOF) {
  while ((rv = readWord(stdin, &word)) != EOF) {
    if (isalnum(rv)) {
      // strcpy(back, word);
      int len = strlen(word);
      back = malloc(len);
      strcpy(back, word);
      for (i = 0; i < 3; i++) {
        char *replace = findData(dictionary, variations[i](word));
        if (replace) {
          printf("%s", replace);
          break;
        }
      }
      if (i == 3) {
        printf("%s", back);
      }
    } else {
      printf("%c", rv);
    }
  }
}
