#include <stdio.h>

#include "file.h"

int main() {
  file_t *F;

  if (!file_open(&F, F_READ, "test.c")) {
    printf("filename : '%s'\n", F->name);
    printf("filesize : %ld\n", F->size);
    file_close(&F);
    file_copy ("test.c", "test.cc");
  }

  return 0;
}
