#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

/*
 * these arguments are pointers to a string, like this:
 *        "adcde=12345\n\0"
 *         |    |      |
 *       line   bk    end
 */
kvpair_t * getKV(char * line, char * bk, char * end) {
  kvpair_t * kv = malloc(sizeof(*kv));

  char ** key = malloc(sizeof(*key));
  *key = malloc(sizeof(**key) * (bk-line+1)); // +1 cause of '\0' should be added.
  for (int i = 0; i < (bk-line+1); i++) {
    (*key)[i] = line[i];
  }
  (*key)[bk-line] = '\0';

  char ** value = malloc(sizeof(*value));
  *value = malloc(sizeof(**value) * (end-bk));
  for (int i = 0; i < (end-bk); i++) {
    (*value)[i] = bk[i+1];
  }
  (*value)[end-bk-1] = '\0';

  kv->key = key;
  kv->value = value;
  return kv;
}


kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * input = fopen(fname, "r");
  if (input == NULL) {
    fprintf(stderr, "Failed to open first file.\n");
    return NULL;
  }

  kvarray_t * kvarray = malloc(sizeof(*kvarray));
  kvarray->kvs = NULL;
  kvarray->length = 0;

  char * line = NULL;
  size_t sz = 0;
  while (getline(&line, &sz, input) >= 0) {
    char * eqidx = strchr(line, '=');
    if (eqidx != NULL) {
      kvarray->length++;
      kvarray->kvs = realloc(kvarray->kvs, sizeof(*kvarray->kvs) * kvarray->length);
      char * endidx = strchr(line, '\n');
      if (endidx == NULL) endidx = strchr(line, '\0');
      kvarray->kvs[kvarray->length-1] = getKV(line, eqidx, endidx);
    }
  }
  free(line);

  if (fclose(input) == EOF) {
    fprintf(stderr, "Failed to close input file.\n");
    return NULL;
  }
  return kvarray;
}

void freeKVs(kvarray_t * pairs) {
  for (int i = 0; i < pairs->length; i++) {
    free(*pairs->kvs[i]->key);
    free(pairs->kvs[i]->key);
    free(*pairs->kvs[i]->value);
    free(pairs->kvs[i]->value);
    free(pairs->kvs[i]);
  }
  free(pairs->kvs);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  for (int i = 0; i < pairs->length; i++) {
    printf("key = '%s' value = '%s'\n", *pairs->kvs[i]->key, *pairs->kvs[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  for (int i = 0; i < pairs->length; i++) {
    if (strcmp(*pairs->kvs[i]->key, key) == 0) {
      return *pairs->kvs[i]->value;
    }
  }
  return NULL;
}
