#include "unity.h"
#include "../src/util.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_mul_bytes() {
    byte arr[2] = { 0x3, 0x4 };
    swap(arr, arr + 1);
    TEST_ASSERT_EQUAL_UINT8(0x3, arr[1]);
    TEST_ASSERT_EQUAL_UINT8(0x4, arr[0]);
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_mul_bytes);
    return UNITY_END();
}
