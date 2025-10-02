#ifndef UTIL_H
#define UTIL_H

#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define FALSE   0
#define TRUE    1
#define HEX_TBL "0123456789abcdef"
#define EN_FREQ "ETAOIN SHRDLU"

unsigned char hexCharToByte(char c);
char byteToBase64(unsigned char b);
char byteToHexChar(unsigned char b);

int occurences(unsigned char* str, size_t len);
void ascii_correct(unsigned char* buf, size_t len);
void xorDecrypt(unsigned char* str, size_t strLen, unsigned char* out, size_t outlen, unsigned char key);

#endif