#include <stdio.h>

void rotate(char matrix[10][10]) {
  for (int i = 0; i < 5; i++) {
    for (int j = i; j < 10-i-1; j++) {
      char tmp = matrix[i][j];
      matrix[i][j] = matrix[10-j-1][i];
      matrix[10-j-1][i] = matrix[10-i-1][10-j-1];
      matrix[10-i-1][10-j-1] = matrix[j][10-i-1];
      matrix[j][10-i-1] = tmp;
    }
  }
}
