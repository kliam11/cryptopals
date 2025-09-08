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

int occurences(unsigned char* str, size_t len,unsigned char c) {
    int count = 0;
    for(size_t i = 0; i < len; i++) {
        if(tolower(str[i]) == tolower(c)) count++;
    }
    return count;
}

void ascii_correct(unsigned char* buf, size_t len) {
    for(int i=0; i<len-1; ++i) {
        if(buf[i] == 0x00) {
            buf[i] = ' ';
        }
    }
}
