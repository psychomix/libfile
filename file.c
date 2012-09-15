/* simple wrapper for file operations */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

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
          fread((*F)->buffer, 1, (*F)->size, in);
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

/*
 return values :
   -1 : *src not found
   -2 : cannot allocate buffer memory
   -3 : cannot create *dst
 */
int file_copy (char *src, char *dst) {
  int r = 0;
  FILE *in, *out;
  uchar *buffer;
  ulong b_size = 1024*1024*10, b_len;
  struct stat sb;

  in = fopen (src, "rb");
  if (in) {
    fprintf (stderr, "%s -> %s\n", src, dst);
    stat (src, &sb);
    buffer = (uchar *)malloc (b_size);
    if (buffer) {
      out = fopen (dst, "wb");
      if (out) {
        do {
          b_len = fread (buffer, 1, b_size, in);
          if (b_len > 0) {
            fwrite (buffer, 1, b_len, out);
          } else break;
        } while (!feof(in));
        fclose (out);
        chmod (dst, sb.st_mode);
        chown (dst, sb.st_uid, sb.st_gid);
      } else r = -3;
      free (buffer);
    } else r = -2;
    fclose (in);
  } else r = -1;
  return (r);
}
