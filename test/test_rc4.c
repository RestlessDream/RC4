#include "unity.h"
#include "../src/rc4.h"
#include "../src/util.h"
#include "stdio.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_encrypt() {
    byte * key = "Key";
    size_t key_len = 3;

    byte * plaintext = "Plaintext";
    size_t pt_len = 9;

    byte expected[9] = { 0xBB, 0xF3, 0x16, 0xE8, 0xD9, 0x40, 0xAF, 0x0A, 0xD3 } ;

    byte output[9];

    init(key, key_len);

    encrypt(plaintext, pt_len, output);

    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, output, 9);
}

void test_decrypt() {
    byte cipher[9] = { 0xBB, 0xF3, 0x16, 0xE8, 0xD9, 0x40, 0xAF, 0x0A, 0xD3 } ;
    size_t pt_len = 9;

    byte * key = "Key";
    size_t key_len = 3;

    byte output[9];

    init(key, key_len);

    decrypt(cipher, pt_len, output);

    byte * plaintext = "Plaintext";

    TEST_ASSERT_EQUAL_UINT8_ARRAY(plaintext, output, 9);
}

void test_encrypt2() {
    byte * key = "Wiki";
    size_t key_len = 4;

    byte * plaintext = "pedia";
    size_t pt_len = 5;

    byte expected[5] = {0x10, 0x21, 0xBF, 0x04, 0x20} ;

    byte output[5];

    init(key, key_len);

    encrypt(plaintext, pt_len, output);

    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, output, 5);
}

void test_decrypt2() {
    byte cipher[5] = {0x10, 0x21, 0xBF, 0x04, 0x20} ;
    size_t pt_len = 5;

    byte * key = "Wiki";
    size_t key_len = 4;

    byte output[5];

    init(key, key_len);

    decrypt(cipher, pt_len, output);

    byte * plaintext = "pedia";

    TEST_ASSERT_EQUAL_UINT8_ARRAY(plaintext, output, 5);
}

void test_encrypt3() {
    byte * key = "Secret";
    size_t key_len = 6;

    byte * plaintext = "Attack at dawn";
    size_t pt_len = 14;

    byte expected[14] = {0x45, 0xA0, 0x1F, 0x64, 0x5F, 0xC3, 0x5B, 0x38, 0x35,
            0x52, 0x54, 0x4B, 0x9B, 0xF5} ;

    byte output[14];

    init(key, key_len);

    encrypt(plaintext, pt_len, output);

    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, output, 14);
}

void test_decrypt3() {
    byte cipher[14] = {0x45, 0xA0, 0x1F, 0x64, 0x5F, 0xC3, 0x5B, 0x38, 0x35,
            0x52, 0x54, 0x4B, 0x9B, 0xF5} ;
    size_t pt_len = 14;

    byte * key = "Secret";
    size_t key_len = 6;

    byte output[14];

    init(key, key_len);

    decrypt(cipher, pt_len, output);

    byte * plaintext = "Attack at dawn";

    TEST_ASSERT_EQUAL_UINT8_ARRAY(plaintext, output, 14);
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_encrypt);
    RUN_TEST(test_decrypt);
    RUN_TEST(test_encrypt2);
    RUN_TEST(test_decrypt2);
    RUN_TEST(test_encrypt3);
    RUN_TEST(test_decrypt3);

    return UNITY_END();
}
