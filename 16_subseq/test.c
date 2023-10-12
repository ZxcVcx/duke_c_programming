#include<stdio.h>
#include<stdlib.h>

size_t maxSeq(int * array, size_t n);

int main(void) {
  int array[] = {3, 5, 4, 6, 7, 1, 2, 3, 4};
  printf("%ld\n", maxSeq(array, 9));
}
