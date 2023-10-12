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
  // TODO:
  // int c = 0;
  // int line = 0;
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      int c = fgetc(f);
      if (c == EOF) {
	fprintf(stderr, "The input doesn't contain enough items.\n");
	return EXIT_FAILURE;
      }
      /* if (j == 10 && c != '\n') { */
      /* 	fprintf(stderr, "The line it to long"); */
      /* 	return EXIT_FAILURE; */
      /* } */
      if (j != 10 && c == '\n') {
	fprintf(stderr, "The line isn't long enough.\n");
	return EXIT_FAILURE;
      }
      matrix[i][j] = c;
    }
    if (fgetc(f) != '\n') {
      fprintf(stderr, "The line is too long.\n");
      return EXIT_FAILURE;
    }
  }
  int endtest = 0;
  while((endtest=fgetc(f)) != EOF) {
    if (endtest != '\n') {
      fprintf(stderr, "The file is too long.\n");
      return EXIT_FAILURE;
    }
  }
  rotate(matrix);
  print_matrix(matrix);
}
