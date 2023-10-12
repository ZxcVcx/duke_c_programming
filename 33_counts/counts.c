#include <stdio.h>

#include <stdlib.h>
#include <string.h>
#include "counts.h"
counts_t * createCounts(void) {
  counts_t * c = malloc(sizeof(*c));
  c->counts = malloc(sizeof(*c->counts));
  *c->counts = NULL;
  c->size = 0;
  c->unknown = 0;
  return c;
}

one_count_t * createCount(const char * name) {
  one_count_t * oc = malloc(sizeof(*oc));
  char ** str = malloc(sizeof(*str));
  *str = malloc(sizeof(**str) * (strlen(name)+1));
  *str = strcpy(*str, name);
  oc->str = str;
  oc->count = 1;
  return oc;
}

int contains(counts_t * c, const char * name) {
  for (int i = 0; i < c->size; i++) {
    if (strcmp(*c->counts[i]->str, name) == 0) {
      return i;
    }
  }
  return -1;
}

void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name == NULL) {
    c->unknown++;
    return;
  }
  int ctn = contains(c, name);
  if (ctn >= 0) {
    c->counts[ctn]->count++;
  } else {
    c->size++;
    c->counts = realloc(c->counts, sizeof(c->counts)*(c->size));
    c->counts[c->size-1] = createCount(name);
  }
}
 
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (int i = 0; i < c->size; i++) {
    fprintf(outFile, "%s: %ld\n", *c->counts[i]->str, c->counts[i]->count);
  }
  if (c->unknown > 0) {
    fprintf(outFile, "<unknown> : %ld\n", c->unknown);
  }
}

void freeCounts(counts_t * c) {
  for (int i = 0; i < c->size; i++) {
    free(*c->counts[i]->str);
    free(c->counts[i]->str);
    free(c->counts[i]);
  }
  free(c->counts);
  free(c);
}
