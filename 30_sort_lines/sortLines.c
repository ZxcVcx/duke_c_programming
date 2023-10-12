#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_input(char *** input, size_t * n, FILE * f) {
  size_t sz = 0;
  char * line = NULL;
  while (getline(&line, &sz, f) >= 0) {
    *input = realloc(*input, (*n+1) * sizeof(*input));
    (*input)[*n] = line;
    line = NULL;
    (*n)++;
  }
  free(line);
}

void print_data(char ** input, size_t count) {
  for (int i = 0; i < count; i++) {
    printf("%s", input[i]);
  }
}

void free_input(char ** input, size_t count) {
  for (int i = 0; i < count; i++) {
    free(input[i]);
  }
  free(input);
}

//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}

//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void sort_lines_and_print(FILE * f) {
  char ** input = NULL;
  size_t count = 0;
  read_input(&input, &count, f);
  sortData(input, count);
  print_data(input, count);
  free_input(input, count);
}

int main(int argc, char ** argv) {
  
  //WRITE YOUR CODE HERE!
  if (argc == 1) {
    sort_lines_and_print(stdin);
  };
  if (argc > 1) {
    for (int i = 1; i < argc; i++) {
      FILE * f = fopen(argv[i], "r");
      if (f == NULL) {
	fprintf(stderr, "The file %s can't be opened.\n", argv[i]);
	return EXIT_FAILURE;
      }
      sort_lines_and_print(f);
      if (fclose(f) == EOF) {
	fprintf(stderr, "Failed to close the file %s.\n", argv[i]);
	return EXIT_FAILURE;
      }
    }
  }
  return EXIT_SUCCESS;
}
