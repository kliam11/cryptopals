#include "crypt.h"

void base64encode(unsigned char* raw, size_t len, char* out, size_t* out_len) {
    int i;
    for(i=0; i<len*8; i+=6) {
        int j = i/8;
        int r = i%8;
        unsigned char high = raw[j] << r;
        high = high >> 2;
        unsigned char low = raw[j+1] >> (10-r);
        unsigned char chunk = (unsigned char)(high + low);
        out[i/6] = byteToBase64(chunk);
    }

    out[i/6] = '\0';
    *out_len = i/6;
}

int hexDecode(const char* hex, size_t len, unsigned char* out, size_t* out_len) {
    if(len%2 != 0) return FALSE;

    int i;
    for(i=0; i<len/2; ++i) {
        char c1 = hex[2*i];
        char c2 = hex[2*i+1];
        unsigned char high = hexCharToByte(c1);
        unsigned char low = hexCharToByte(c2);
        out[i] = (high << 4) | low;
    }
    out[i] = 0;
    *out_len = i;

    return TRUE;
}

int hexEncode(unsigned char* raw, size_t len, char* out, size_t* out_len) {
    int i;
    for(i=1; i<len*2; i+=2) {
        unsigned char b = raw[i/2];
        unsigned char high = b >> 4;
        unsigned char low = b;
        char hex1 = byteToHexChar(high);
        char hex2 = byteToHexChar(low);
        out[i-1] = hex1;
        out[i] = hex2;

    }
    out[i] = '\0';
    *out_len = i;

    return TRUE;
}

int fixedXOR(unsigned char* str1, size_t str1len, 
                unsigned char* str2, size_t str2len, 
                unsigned char* out) 
{
    if(str1len != str2len) return FALSE;

    unsigned char* p1 = str1;
    unsigned char* p2 = str2;
    unsigned char* o = out;

    while(str1len--) {
        *o++ = *p1++ ^ *p2++;
    }
    *o = 0;

    return TRUE;
}

void singleXOR_attack(unsigned char* str, size_t strLen, unsigned char* fndKey) {
    int maxScore = 0;
    unsigned char key;

    for(int i=0; i<256; ++i) {
        int score = 0;
        unsigned char k = (unsigned char)i;
        unsigned char xorBuf[strLen];

        for(int j=0; j<strLen; ++j) {
            xorBuf[j] = str[j] ^ k;
        }

        for(const char* p=EN_FREQ; *p!='\0'; p++) {
            score += occurences(xorBuf, strLen, (unsigned char)*p);
        }

        if(score>maxScore) {
            maxScore = score;
            key = k;
        }
    }

    *fndKey = key;
}