/* simple wrapper for file operations */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "file.h"

/*
 return values :
   -1 : unable to allocate memory for *F
   -2 : unknown mode
   -3 : unable to open file
   -4 : unable to allocate memory for buffer
 */
int file_open(file_t ** F, int mode, char *name) {
  int r = 0;
  FILE *in;

  *F = (file_t *) malloc(sizeof(file_t));
  if (*F) {
    if (mode & F_READ) {
      (*F)->name = strdup(name);
      in = fopen(name, "rb");
      if (in) {
	fseek(in, 0, SEEK_END);
	(*F)->size = ftell(in);
	rewind(in);
	(*F)->buffer = (uchar *) malloc((*F)->size);
	if ((*F)->buffer) {
	  fread((*F)->buffer, (*F)->size, 1, in);
	} else
	  r = -4;
	fclose(in);
      } else
	r = -3;
    } else
      r = -2;
  } else
    r = -1;

  return (r);
}

/*
 return values :
   -1 : *F not allocated
 */

int file_close(file_t ** F) {
  int r = 0;

  if (*F) {
    free((*F)->name);
    free(*F);
  } else
    r = -1;

  return (r);
}
