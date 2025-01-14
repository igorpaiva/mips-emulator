#include "rktest/rktest.h"
#include "memory.h"

TEST_SETUP(memory_tests) {
    reset_registers_and_memory();
}

TEST(memory_tests, reset_registers) {
    for (int i = 0; i < 32; i++) {
        EXPECT_EQ(registers[i], 0);
    }
}

TEST(memory_tests, reset_memory) {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        EXPECT_EQ(memory[i], 0);
    }
}
