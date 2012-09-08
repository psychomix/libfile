#ifndef _FILE_H
#define _FILE_H

#define F_READ (1<<0)

#include "types.h"

typedef struct {
  char *name;
  char *buffer;
  ulong size;
} file_t;

extern int file_open  (file_t **F, int mode, char *name);
extern int file_close (file_t **F);

#endif
