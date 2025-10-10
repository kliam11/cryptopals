#include "encoding.h"

char _byteToHexChar(unsigned char b);
unsigned char _hexCharToByte(char c);

void base64encode(unsigned char* raw, size_t len, char* out, size_t* out_len) {
    size_t i, o = 0;

    for (i = 0; i + 2 < len; i += 3) {
        unsigned int val = (raw[i] << 16) | (raw[i + 1] << 8) | raw[i + 2];
        out[o++] = B64_TBL[(val >> 18) & 0x3F];
        out[o++] = B64_TBL[(val >> 12) & 0x3F];
        out[o++] = B64_TBL[(val >> 6)  & 0x3F];
        out[o++] = B64_TBL[val & 0x3F];
    }

    if (i < len) {
        unsigned int val = raw[i] << 16;
        if (i + 1 < len) val |= raw[i + 1] << 8;
        out[o++] = B64_TBL[(val >> 18) & 0x3F];
        out[o++] = B64_TBL[(val >> 12) & 0x3F];
        out[o++] = (i + 1 < len) ? B64_TBL[(val >> 6) & 0x3F] : '=';
        out[o++] = '=';
    }

    out[o] = '\0';
    *out_len = o;
}

cryptop_errno hexDecode(char* hex, size_t len, unsigned char* out, size_t* out_len) {
    size_t o = 0;
    unsigned char high = 0;
    int have_high = 0;

    for (size_t i = 0; i < len; ++i) {
        char c = hex[i];
        if (c == '\n' || c == '\r') continue;
        if (c == ' ' || c == '\t') continue;

        unsigned char val = _hexCharToByte(c);

        if (!have_high) {
            high = val;
            have_high = 1;
        } else {
            out[o++] = (high << 4) | val;
            have_high = 0;
        }
    }

    if (have_high) {
        return CRYPTOP_NOK;
    }

    out[o] = 0;
    *out_len = o;
    return CRYPTOP_OK;
}

cryptop_errno hexEncode(unsigned char* raw, size_t len, char* out, size_t* out_len) {
    size_t i;
    for (i = 0; i < len; ++i) {
        unsigned char b = raw[i];
        out[i * 2]     = _byteToHexChar(b >> 4);
        out[i * 2 + 1] = _byteToHexChar(b & 0x0F);
    }
    out[i * 2] = '\0';
    *out_len = i * 2;
    return CRYPTOP_OK;
}

unsigned char _hexCharToByte(char c) {
    if (c >= '0' && c <= '9') {
        return (unsigned char) (c - '0');
    } else if (c >= 'a' && c <= 'z') {
        return (unsigned char) (c - 'a') + 10;
    } else {
        return (unsigned char) (c - 'A') + 10;
    }
}

char _byteToHexChar(unsigned char b) {
    return HEX_TBL[b & 0xF];
}
