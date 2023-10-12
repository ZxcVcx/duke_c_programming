#include<stdio.h>
#include<stdlib.h>

void updateMax(size_t * max, size_t * current) {
  if (*current > *max) {
    *max = *current;
  }
  *current = 0;
}

size_t maxSeq(int * array, size_t n) {
  if (n == 0 || n == 1) return n;
  
  size_t max = 0;
  size_t current = 0;
  for (int i = 0; i < n - 1; i++) {
    current++;

    if ((i == n-2 && array[n-2] < array[n-1])) {
      current++;
      updateMax(&max, &current);
    }
    if (array[i+1] <= array[i]) {
      updateMax(&max, &current);
    }
  }
  
  return max;
}
