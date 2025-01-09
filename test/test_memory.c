#include "unity.h"
#include "memory.h"

void setUp(void) {
    // Set up before each test
    reset_registers_and_memory();
}

void tearDown(void) {
    // Clean up after each test
}

void test_reset_registers(void) {
    for (int i = 0; i < 32; i++) {
        TEST_ASSERT_EQUAL_UINT32(0, registers[i]);
    }
}

void test_reset_memory(void) {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        TEST_ASSERT_EQUAL_UINT8(0, memory[i]);
    }
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_reset_registers);
    RUN_TEST(test_reset_memory);
    return UNITY_END();
}