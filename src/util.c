#include "util.h"

unsigned char hexCharToByte(char c) {
    if (c >= '0' && c <= '9') {
        return (unsigned char) (c - '0');
    } else if (c >= 'a' && c <= 'z') {
        return (unsigned char) (c - 'a') + 10;
    } else {
        return (unsigned char) (c - 'A') + 10;
    }
}

char byteToHexChar(unsigned char b) {
    return HEX_TBL[b & 0xF];
}

char byteToBase64(unsigned char b) {
    if (b >= 0 && b < 26) {
        return (char) (b + 'A');
    } else if (b >= 26 && b < 52) {
        return (char) ((b - 26) + 'a');
    } else if (b >= 52 && b < 62) {
        return (char) ((b - 52) + '0');
    } else if (b == 62) {
        return '+';
    } else {
        return '/';
    }
}

int occurences(unsigned char* str, size_t len) {
    int score = 0;
    for(const char* p=EN_FREQ; *p!='\0'; p++) {
        for(size_t i = 0; i < len; i++) {
            if(tolower(str[i]) == tolower(*p)) score++;
        }
    }
    return score;
}

void ascii_correct(unsigned char* buf, size_t len) {
    for(int i=0; i<len-1; ++i) {
        if(buf[i] == 0x00) {
            buf[i] = ' ';
        }
    }
}

void xorDecrypt(unsigned char* str, size_t strLen, unsigned char* out, size_t outlen, unsigned char key) {
    for (int i = 0; i < strLen; ++i) {
        out[i] = str[i] ^ key;
    }
    out[outlen] = 0;

    ascii_correct(out, outlen);
}