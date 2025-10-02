#include "io.h"

int readFile(const char* filename, char** data, long* datalen) {
    long len;
    if(!getFileLen(filename, &len)){
        return FALSE;
    }
    
    FILE* f;
    f = fopen(filename, "r");
    if(f == NULL) return FALSE;
    
    char* d = malloc(len+1);
    if(d == NULL) return FALSE;
    fread(d, 1, len, f);
    *data = (char*)d;
    *datalen = len;
    
    fclose(f);
    return TRUE;
}

int getFileLen(const char* filename, long* rlen) {
    FILE* f;
    f = fopen(filename, "r");
    if(f == NULL) {
        perror("Unable to open file\n");
        return FALSE;
    }
    long pos = ftell(f);
    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    *rlen = len;
    rewind(f);
    fclose(f);
    return TRUE;
}

