#include <stdlib.h>
#include <stdio.h>
unsigned power(unsigned x, unsigned y);
void run_check(unsigned x, unsigned y, unsigned expected_a) {
  if (power(x, y) != expected_a) {
    printf("The %u power of %u is %u\n", y, x, power(x, y));
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  run_check(0, 0, 1);
  run_check(10, 0, 1);
  run_check(0, 1, 0);
  run_check(10, 2, 100);
  run_check(1, 1, 1);
  run_check(1, 1000, 1);
  run_check(1000, 2, 1000000);
  return EXIT_SUCCESS;
}
