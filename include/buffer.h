#ifndef BUFFER_H
#define BUFFER_H

#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "cryptop_err.h"

typedef struct buffer_instance_t* buffer_t;

buffer_t buffer_create();
void buffer_destroy(buffer_t buffer);

cryptop_errno buffer_add(buffer_t buffer, unsigned char* data, size_t data_l, size_t* loc);
cryptop_errno buffer_get_count(buffer_t buffer, size_t* count_p);
cryptop_errno buffer_get(buffer_t buffer, size_t index, unsigned char** data_p, size_t* data_l);
cryptop_errno buffer_remove(buffer_t buffer, size_t index);

#endif