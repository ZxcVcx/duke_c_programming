#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

int encptkey(FILE * f) {
  int counts[26] = {0};
  int c = 0;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      counts[c-'a']++;
    }
  }

  int max = 0;
  for (int i = 0; i < 26; i++) {
    if (counts[max] < counts[i]) {
      max = i;
    }
  }
  return max + 'a' - 'e';
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: break <filename>\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Open failed, ensure th file existed and you have the read promission\n");
    return EXIT_FAILURE;
  }
  int key = encptkey(f);
  printf("%d\n", key);
  return EXIT_SUCCESS;
}
