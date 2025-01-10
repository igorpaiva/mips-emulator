#include "rktest/rktest.h"
#include "memory.h"

// Helper: Setup function
void setup(void) {
    reset_registers_and_memory();
}

// Test case: Check if registers are reset
TEST(memory_tests, reset_registers) {
    setup();
    for (int i = 0; i < 32; i++) {
        EXPECT_EQ(registers[i], 0);
    }
}

// Test case: Check if memory is reset
TEST(memory_tests, reset_memory) {
    setup();
    for (int i = 0; i < MEMORY_SIZE; i++) {
        EXPECT_EQ(memory[i], 0);
    }
}
