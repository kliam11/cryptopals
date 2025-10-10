#ifndef ERRORS_H
#define ERRORS_H

typedef enum {
    CRYPTOP_NOK = 0,
    CRYPTOP_OK = 1,
    CRYPTOP_ERR_ALLOC = -1,
    CRYPTOP_ERR_INVALID = -2,
    CRYPTOP_ERR_UNSUPPORTED = -3,
    CRYPTOP_ERR_NOMEM = -4,
    CRYPTOP_ERR_NULLPTR = -5,
    CRYPTOP_ERR_OUTOFINDEX = -6,
} cryptop_errno;

#endif