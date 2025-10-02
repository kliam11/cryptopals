#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

int readFile(const char* filename, char** data, long* datalen);
int getFileLen(const char* filename, long* rlen);

#endif