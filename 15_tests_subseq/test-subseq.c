#include<stdio.h>
#include<stdlib.h>

size_t maxSeq(int * array, size_t n);

int main(void) {
  int array1[] = {2, 4, 6, -1};
  if (maxSeq(array1, 4) != 3) { printf("array1, %ld\n", maxSeq(array1, 4)); return EXIT_FAILURE; }
  
  int array2[] = {1, 3, 5, 2, 4, 6, -1};
  if (maxSeq(array2, 7) != 3) { printf("array2, %ld\n", maxSeq(array2, 7)); return EXIT_FAILURE; }

  int array3[4] = {0};
  if (maxSeq(array3, 4) != 1) { printf("array3, %ld\n", maxSeq(array3, 4)); return EXIT_FAILURE; }

  int array4[4] = {0};
  if (maxSeq(array4, 0) != 0) { printf("array4, %ld\n", maxSeq(array3, 0)); return EXIT_FAILURE; }

  int array5[] = {0, -3, 5, -8};
  if (maxSeq(array5, 4) != 2) { printf("array5, %ld\n", maxSeq(array5, 4)); return EXIT_FAILURE; }

  int array6[] = {0, -3, 5, -8};
  if (maxSeq(array6, 2) != 1) { printf("array6, %ld\n", maxSeq(array6, 2)); return EXIT_FAILURE; }

  printf("ok\n");
  return EXIT_SUCCESS;
}
