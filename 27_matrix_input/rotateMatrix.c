#include<stdio.h>
#include<stdlib.h>


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


void print_matrix(char matrix[10][10]) {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      printf("%c", matrix[i][j]);
    }
    printf("\n");
  }
}


int end_test(FILE * f) {
  int endtest = 0;
  while((endtest=fgetc(f)) != EOF) {
    if (endtest != '\n') {
      fprintf(stderr, "The file is too long.\n");
      return 1;
    }
  }
  return 0;
}


int read_matrix(char matrix[10][10], FILE * f) {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      int c = fgetc(f);
      if (c == EOF) {
	fprintf(stderr, "The input doesn't contain enough items.\n");
	return 1;
      }
      if (j != 10 && c == '\n') {
	fprintf(stderr, "The line isn't long enough.\n");
	return 1;
      }
      matrix[i][j] = c;
    }
    if (fgetc(f) != '\n') {
      fprintf(stderr, "The line is too long.\n");
      return 1;
    }
  }
  return 0;
}


int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: rotate <filename>\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "File isn't exist, or user doesn't have the promission to read the file.\n");
    return EXIT_FAILURE;
  }
  
  char matrix[10][10] = {0};
  if (read_matrix(matrix, f)) {
    return EXIT_FAILURE;
  }
  if (end_test(f)) {
    return EXIT_FAILURE;
  }
  rotate(matrix);
  print_matrix(matrix);

  if (fclose(f) != 0) {
    fprintf(stderr, "Failed to close the file.\n");
  }
}
