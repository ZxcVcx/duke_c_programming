#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  char * out = NULL;
  out = malloc(strlen(inputName) + 8);
  strcpy(out, inputName);
  strcat(out, ".counts");
  return out;
}
