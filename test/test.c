#include "test.h"

// Challenge 1
static void test_HexToBase64(void** state) {
    char* input = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    char* exp = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";
    
    unsigned char hexOut[256] = {0};
    size_t hexOut_l = 0;
    if(hexDecode(input, strlen(input), hexOut, &hexOut_l) == CRYPTOP_NOK){
        fail_msg("Hex Decoding returned NOK");
    }
    
    char b64out[256] = {0};
    size_t b64out_l = 0;
    base64encode(hexOut, hexOut_l, b64out, &b64out_l);
    
    assert_string_equal(exp, b64out);
}

// Challenge 2
void test_FixedXor(void** state) {
    char* in1 = "1c0111001f010100061a024b53535009181c";
    char* in2 = "686974207468652062756c6c277320657965";
    char* exp = "746865206b696420646f6e277420706c6179";

    unsigned char hexDec1[256] = {0};
    unsigned char hexDec2[256] = {0};
    size_t hexDec1_l, hexDec2_l = 0;
    if((hexDecode(in1, strlen(in1), hexDec1, &hexDec1_l) == CRYPTOP_NOK)
        || (hexDecode(in2, strlen(in2), hexDec2, &hexDec2_l) == CRYPTOP_NOK)){
        fail_msg("Hex Decoding returned NOK");
    }

    unsigned char* inputs[] = { hexDec1, hexDec2 };
    size_t inputs_l[] = { hexDec1_l, hexDec2_l };
    xor_t xor_p = xor_create(inputs, inputs_l, 2);
    if(xor_p == NULL) {
        fail_msg("xor_create returned NULL");
    }

    size_t out_ind = 0;
    xor_do(xor_p, 0, 1, &out_ind);

    unsigned char* result = NULL;
    size_t result_l = 0;
    if(xor_get_output(xor_p, out_ind, &result, &result_l) != CRYPTOP_OK) {
        fail_msg("xor_get_output retunred error");
    }

    char hexEnc[256] = {0};
    size_t hexEnc_l = 0;
    if(hexEncode(result, result_l, hexEnc, &hexEnc_l) == CRYPTOP_NOK) {
        xor_destroy(xor_p);
        fail_msg("Hex Encoding returned NOK");
    }

    assert_string_equal(exp, hexEnc);
    xor_destroy(xor_p);
}

// Challenge 5
void test_RepeatKeyXor(void** state) {
    char* in1 = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
    char* in2 = "ICE";
    char* exp = "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f";

    unsigned char* inputs[] = { (unsigned char*)in1, (unsigned char*)in2 };
    size_t inputs_l[] = { strlen(in1), strlen(in2) };
    xor_t xor_p = xor_create(inputs, inputs_l, 2);
    if(xor_p == NULL) {
        fail_msg("xor_create returned NULL");
    }

    size_t out_ind = 0;
    xor_do(xor_p, 0, 1, &out_ind);

    unsigned char* result = NULL;
    size_t result_l = 0;
    if(xor_get_output(xor_p, out_ind, &result, &result_l) != CRYPTOP_OK) {
        fail_msg("xor_get_output retunred error");
    }

    char hexEnc[256] = {0};
    size_t hexEnc_l = 0;
    if(hexEncode(result, result_l, hexEnc, &hexEnc_l) == CRYPTOP_NOK) {
        xor_destroy(xor_p);
        fail_msg("Hex Encoding returned NOK");
    }

    assert_string_equal(exp, hexEnc);
    xor_destroy(xor_p);
}

// Challenge 4
void test_DetectSingleCharXor(void** state) {
    char* in = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    cipher_type exp = XOR_SINGLE;

    unsigned char hexDec[256] = {0};
    size_t hexDec_l = 0;
    if(hexDecode(in, strlen(in), hexDec, &hexDec_l) == CRYPTOP_NOK){
        fail_msg("Hex Decoding returned NOK");
    }

    unsigned char* inputs[] = { hexDec };
    size_t inputs_l[] = { hexDec_l };
    xor_t xor_p = xor_create(inputs, inputs_l, 1);
    if(xor_p == NULL) {
        fail_msg("xor_create returned NULL");
    }

    cipher_type ciph_t;
    if(xor_detect_type(xor_p, 0, &ciph_t) != CRYPTOP_OK) {
        fail_msg("xor_detect_type returned NOK");
    }

    assert_int_equal(exp, ciph_t);
    xor_destroy(xor_p);
}
/*
void test_DetectPlainText(void** state) {
    char* in = "05f12f380720ea2b19e24a07e53c142128354e2827f25a08fb401c3126a6";
    cipher_type exp = XOR_PLAIN;

    unsigned char hexDec[256] = {0};
    size_t hexDec_l = 0;
    if(hexDecode(in, strlen(in), hexDec, &hexDec_l) == CRYPTOP_NOK){
        fail_msg("Hex Decoding returned NOK");
    }

    unsigned char* inputs[] = { hexDec };
    size_t inputs_l[] = { hexDec_l };
    xor_t xor_p = xor_create(inputs, inputs_l, 1);
    if(xor_p == NULL) {
        fail_msg("xor_create returned NULL");
    }

    cipher_type ciph_t;
    if(xor_detect_type(xor_p, 0, &ciph_t) != CRYPTOP_OK) {
        fail_msg("xor_detect_type returned NOK");
    }

    assert_int_equal(exp, ciph_t);
    xor_destroy(xor_p);
}

void test_DecryptSingleCharXor(void** state) {
    char* in = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    char* exp = "Cooking MC's like a pound of bacon";

    unsigned char hexDec[256] = {0};
    size_t hexDec_l = 0;
    if(hexDecode(in, strlen(in), hexDec, &hexDec_l) == CRYPTOP_NOK){
        fail_msg("Hex Decoding returned NOK");
    }

    unsigned char* inputs[] = { hexDec };
    size_t inputs_l[] = { hexDec_l };
    xor_t xor_p = xor_create(inputs, inputs_l, 1);
    if(xor_p == NULL) {
        fail_msg("xor_create returned NULL");
    }

    size_t key_ind;
    //xor_compute_key_singlechar(xor_p, 0, &key_ind);

    assert_int_equal(exp, ciph_t);
    xor_destroy(xor_p);
} */

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_HexToBase64),
        cmocka_unit_test(test_FixedXor),
        cmocka_unit_test(test_RepeatKeyXor),
        //cmocka_unit_test(test_DetectSingleCharXor),
        //cmocka_unit_test(test_DetectPlainText),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}