#ifndef XOR_H
#define XOR_H

#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "cryptop_err.h"
#include "util.h"
#include "buffer.h"

#define EN_FREQ "ETAOIN SHRDLU"
#define CHAR_MAX 256

#define SHAN_THRES_PLAIN 3.0
#define SHAN_THRES_SINGLE 6.5
#define SHAN_THRES_MULTI 7.8

typedef enum {
    XOR_PLAIN = 1,
    XOR_SINGLE = 2,
    XOR_BLOCK = 3,
} cipher_type;

typedef struct xor_instance_t* xor_t;

xor_t xor_create(unsigned char** inputs, size_t* inputs_l, size_t inputs_count);
void xor_destroy(xor_t xor_p);

cryptop_errno xor_get_output(xor_t xor_p, size_t index, unsigned char** out, size_t* out_l);
cryptop_errno xor_get_key(xor_t xor_p, size_t index, unsigned char** key, size_t* out_l);

cryptop_errno xor_do(xor_t xor_p, size_t index1, size_t index2, size_t* out_ind);
cryptop_errno xor_detect_type(xor_t xor_p, size_t index, cipher_type* type);
cryptop_errno xor_compute_key_singlechar(xor_t xor_p, size_t index, size_t* key_ind);
cryptop_errno xor_compute_key_multipchar(xor_t xor_p, unsigned char sep, size_t* key_ind);

#endif