#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

char * stripNewline(char * str) {
  char * ptr = strchr(str, '\n');
  if (ptr != NULL) {
    *ptr = '\0';
  }
  return str;
}
counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  counts_t * count_file = createCounts();

  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "Failed to open %s.", filename);
    return NULL;
  }

  char * line = NULL;
  size_t sz = 0;
  while (getline(&line, &sz, f) >= 0) {
    addCount(count_file, lookupValue(kvPairs, stripNewline(line)));
  }
  free(line);
  
  if (fclose(f) == EOF) {
    fprintf(stderr, "Failed to close %s.", filename);
    return NULL;
  }
  
  return count_file;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
 //read the key/value pairs from the file named by argv[1] (call the result kv)
  if (argc < 2) {
    fprintf(stderr, "Usage: count_values <kvs.txt> <value1.txt> <value2.txt> ...\n");
    return EXIT_FAILURE;
  }
  kvarray_t * kv = readKVs(argv[1]);
  if (kv == NULL) {
    return EXIT_FAILURE;
  }
  
 //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], kv);
    if (c == NULL) {
      return EXIT_FAILURE;
    }
    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);

    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    if (f == NULL) {
      fprintf(stderr, "Failed to open/create %s\n", outName);
      return EXIT_FAILURE;
    }
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    if (fclose(f) == EOF) {
      fprintf(stderr, "Failed to close %s\n", outName);
      return EXIT_FAILURE;
    }
    //free the memory for outName and c
    free(outName);
    freeCounts(c);
  }

 //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}
