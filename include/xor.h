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

#define CHAR_MAX 256

#define SHAN_THRES_PLAIN 2.0
#define SHAN_THRES_SINGLE 6.5
#define SHAN_THRES_MULTI 7.8

#define EN_FREQ_TBL { \
    8.55, /* A */ \
    1.60, /* B */ \
    3.16, /* C */ \
    3.87, /* D */ \
    12.10,/* E */ \
    2.18, /* F */ \
    2.09, /* G */ \
    4.96, /* H */ \
    7.33, /* I */ \
    0.22, /* J */ \
    0.81, /* K */ \
    4.21, /* L */ \
    2.53, /* M */ \
    7.17, /* N */ \
    7.47, /* O */ \
    2.07, /* P */ \
    0.10, /* Q */ \
    6.33, /* R */ \
    6.73, /* S */ \
    8.94, /* T */ \
    2.68, /* U */ \
    1.06, /* V */ \
    1.83, /* W */ \
    0.19, /* X */ \
    1.72, /* Y */ \
    0.11  /* Z */ \
}

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