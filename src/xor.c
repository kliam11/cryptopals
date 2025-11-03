#include "xor.h"

double _compute_entropy(unsigned char* in, size_t len);
double _compute_chisq(unsigned char* in, size_t len);
int _compute_hamming(unsigned char* in1, unsigned char* in2, size_t len);

struct xor_instance_t {
    buffer_t inputs;
    buffer_t outputs;
    buffer_t keys;
};

xor_t xor_create(unsigned char** inputs, size_t* inputs_l, size_t inputs_count)
{
    xor_t p = malloc(sizeof(struct xor_instance_t));
    if(p == NULL) return NULL;

    p->inputs = buffer_create();
    p->outputs = buffer_create();
    p->keys = buffer_create();
    if(p->inputs == NULL || p->outputs == NULL || p->keys == NULL) {
        xor_destroy(p);
        return NULL;
    }

    for(int i=0; i<inputs_count; ++i) {
        if(buffer_add(p->inputs, inputs[i], inputs_l[i], NULL) == CRYPTOP_OK) continue;
        else {
            xor_destroy(p);
            return NULL;
        }
    }

    return p;
}

void xor_destroy(xor_t xor_p) {
    if(xor_p == NULL) return;
    buffer_destroy(xor_p->inputs);
    buffer_destroy(xor_p->outputs);
    buffer_destroy(xor_p->keys);
    free(xor_p);
}

cryptop_errno xor_get_output(xor_t xor_p, size_t index, unsigned char** out, size_t* out_l) {
    if(xor_p == NULL) return CRYPTOP_ERR_NULLPTR;

    unsigned char* p = NULL;
    size_t p_l;
    cryptop_errno err = buffer_get(xor_p->outputs, index, &p, &p_l);
    if(err == CRYPTOP_OK) {
        *out = p;
        *out_l = p_l;
        return CRYPTOP_OK;
    }
    return err;
}

cryptop_errno xor_get_key(xor_t xor_p, size_t index, unsigned char** key, size_t* key_l) {
    if(xor_p == NULL) return CRYPTOP_ERR_NULLPTR;

    unsigned char* p = NULL;
    size_t p_l;
    cryptop_errno err = buffer_get(xor_p->keys, index, &p, &p_l);
    if(err == CRYPTOP_OK) {
        *key = p;
        *key_l = p_l;
        return CRYPTOP_OK;
    }
    return err;
}

cryptop_errno xor_do(xor_t xor_p, size_t index1, size_t index2, size_t* out_ind) {
    if (xor_p == NULL) return CRYPTOP_ERR_NULLPTR;

    unsigned char *b1 = NULL, *b2 = NULL;
    size_t b1_l = 0, b2_l = 0;

    cryptop_errno b1_err = buffer_get(xor_p->inputs, index1, &b1, &b1_l);
    cryptop_errno b2_err = buffer_get(xor_p->inputs, index2, &b2, &b2_l);
    if (b1_err != CRYPTOP_OK || b2_err != CRYPTOP_OK)
        return CRYPTOP_ERR_OUTOFINDEX;

    size_t max_l = b1_l;
    size_t min_l = b2_l;
    unsigned char *maxStr = b1;
    unsigned char *minStr = b2;
    unsigned char *keystream = b2;
    int allocd = 0;

    if (max_l != min_l) {
        if (max_l < min_l) { 
            size_t t_l = max_l;
            max_l = min_l;
            min_l = t_l;

            unsigned char* t_s = maxStr;
            maxStr = minStr;
            minStr = t_s;
        }

        size_t keystream_l = (max_l + min_l - 1) / min_l;
        keystream = malloc(keystream_l * min_l);
        if (keystream == NULL) return CRYPTOP_ERR_ALLOC;
        allocd = 1;

        for (size_t i = 0; i < keystream_l; ++i) {
            memcpy(keystream + (i * min_l), minStr, min_l);
        }
    }

    unsigned char* result = malloc(max_l);
    if (result == NULL) {
        if (allocd) free(keystream);
        return CRYPTOP_ERR_ALLOC;
    }
    
    for (size_t i = 0; i < max_l; ++i) {
        result[i] = maxStr[i] ^ keystream[i];
    }

    size_t r_loc = 0;
    buffer_add(xor_p->outputs, result, max_l, &r_loc);
    *out_ind = r_loc;

    if (allocd) free(keystream);
    free(result);

    return CRYPTOP_OK;
}

cryptop_errno xor_detect_type(xor_t xor_p, size_t index, cipher_type* type) {
    if(xor_p == NULL) return CRYPTOP_ERR_NULLPTR;

    unsigned char* p = NULL;
    size_t p_l = 0;
    cryptop_errno err = buffer_get(xor_p->inputs, index, &p, &p_l);
    
    if(err == CRYPTOP_OK) {
        double ent = _compute_entropy(p, p_l);
        if(ent <=SHAN_THRES_PLAIN) {
            *type = XOR_PLAIN;
        } 
        else if(ent < SHAN_THRES_SINGLE) {
            // do chi-squared test
                // y? :: XOR_SINGLE
                // n? :: XOR_PLAIN
            *type = XOR_SINGLE;
        } 
        else {
            *type = XOR_BLOCK;
        }
        return CRYPTOP_OK;
    }
    
    return err;
}

cryptop_errno xor_compute_key_singlechar(xor_t xor_p, size_t index, size_t* key_ind) {
    
}

double _compute_entropy(unsigned char* in, size_t len) {
    size_t freq[256] = {0};
    for(size_t i=0; i<len; ++i) {
        freq[in[i]]++;
    }

    double ent = 0.0;
    for(int i=0; i<256; ++i) {
        if(freq[i] == 0) continue;
        double p = (double)freq[i] / (double)len;
        ent -= p * log2(p);
    }
    return ent;
}

double _compute_chisq(unsigned char* in, size_t len) {
    
}

int _compute_hamming(unsigned char* in1, unsigned char* in2, size_t len) {
    int d = 0;
    for(int i=0; i<len; ++i) {
        unsigned char c = in1[i] ^ in2[i];
        while(c) {
            d++;
            c &= (c-1);
        }
    }
    return d;
}