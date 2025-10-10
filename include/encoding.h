#ifndef ENCODING_H
#define ENCODING_H

#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "cryptop_err.h"

#define HEX_TBL "0123456789abcdef"
#define B64_TBL "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"

/**
 * Encodes single or multiline byte array to base64
 * 
 * Input:
 *      unsigned char* raw: byte array
 *      size_t len: length of raw
 *      char* out: pointer to output array
 *      size_t* out_len: pointer to output length
 */
void base64encode(unsigned char* raw, size_t len, char* out, size_t* out_len);

/**
 * Decodes single or multiline hex array
 * 
 * Input:
 *      char* hex: hex array
 *      size_t len: length of hex
 *      unsigned char* out: pointer to output array
 *      size_t* out_len: pointer to output length
 */
cryptop_errno hexDecode(char* hex, size_t len, unsigned char* out, size_t* out_len);

/**
 * Encodes byte array to hex
 * 
 * Input:
 *      unsigned char* raw: byte array
 *      size_t len: length of raw
 *      char* out: pointer to output array
 *      size_t* out_len: pointer to output length
 */
cryptop_errno hexEncode(unsigned char* raw, size_t len, char* out, size_t* out_len);

#endif