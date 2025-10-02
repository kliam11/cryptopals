#include "crypt.h"
#include "util.h"

int doBase64Encode(char* hexStr) {
    unsigned char hexArr[256];
    char b64[256];
    size_t hexOut_l, b64Out_len;

    hexDecode(hexStr, strlen(hexStr), hexArr, &hexOut_l);
    base64encode(hexArr, hexOut_l, b64, &b64Out_len);
    
    printf("%s\n", b64);
    return TRUE;
}

int doFixedXOR(char* hexStr1, char* hexStr2) {
    unsigned char hexArr1[256];
    unsigned char hexArr2[256];
    size_t hexArr1_l, hexArr2_l;

    hexDecode(hexStr1, strlen(hexStr1), hexArr1, &hexArr1_l);
    hexDecode(hexStr2, strlen(hexStr2), hexArr2, &hexArr2_l);

    unsigned char XORout[256];
    fixedXOR(hexArr1, hexArr1_l, hexArr2, hexArr2_l, XORout);

    char out[256];
    size_t out_l;
    hexEncode(XORout, hexArr1_l, out, &out_l);

    printf("%s\n", out);
    return TRUE;
}

int doSingleXORcipher(char* hexStr) {
    unsigned char byteBuf[256];
    size_t byteBuf_l;

    hexDecode(hexStr, strlen(hexStr), byteBuf, &byteBuf_l);

    unsigned char key;
    int scr;
    singleXOR_attack(byteBuf, byteBuf_l, &key, &scr);
    printf("Found key: 0x%02X ('%c')\n", key, key);

    unsigned char out[256];
    xorDecrypt(byteBuf, byteBuf_l, out, byteBuf_l, key);
    printf("%s\n", out);
    
    return TRUE;
}

int doSingleXORcipher_file(char* file){
    char* d;
    long len;
    if(!readFile(file, &d, &len)) {
        return FALSE;
    }

    int lineNum;
    unsigned char fndKey;
    unsigned char* fndText = malloc(60);
    int fndTextLen;
    singleXOR_attackFile(d, len, &lineNum, &fndKey, &fndText, &fndTextLen);
    

    printf("Line of fnd ciphertext: %d\n", lineNum);
    xorDecrypt(fndText, fndTextLen, fndText, fndTextLen, fndKey);
    printf("Deciphered msg of ciphertext: %s\n", fndText);
    
    free(d);
    free(fndText);

    return TRUE;
}

int main(int argc, char **argv)  {
    doBase64Encode("49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d");
    doFixedXOR("1c0111001f010100061a024b53535009181c", "686974207468652062756c6c277320657965");
    doSingleXORcipher("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736");
    doSingleXORcipher_file("./files/ch4.txt");

    return 0;
}
