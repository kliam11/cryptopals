#ifndef CRYPT_H
#define CRYPT_H

#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "util.h"
#include "io.h"

void base64encode(unsigned char* raw, size_t len, char* out, size_t* out_len);
int hexDecode(const char* hex, size_t len, unsigned char* out, size_t* out_len);
int hexEncode(unsigned char* raw, size_t len, char* out, size_t* out_len);
int fixedXOR(unsigned char* decodedHex1, size_t decodedHex1len, unsigned char* decodedHex2, size_t deocdedHex2len, unsigned char* out);
void singleXOR_attack(unsigned char* str, size_t strLen, unsigned char* fndKey, int* scr);
void singleXOR_attackFile(char* filebuf, long filebufLen, int* lineNum, unsigned char* fndKey, unsigned char** fndText, int* fndTextLen);

#endif