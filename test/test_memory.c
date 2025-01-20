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

TEST(memory_tests, reset_pc) {
    reset_pc();
    EXPECT_EQ(pc, PC_START);
}

TEST(memory_tests, store_string_in_memory) {
    char *string = "Hello, World!";
    store_string_in_memory(string, 0x100);
    for (int i = 0; i < (int)strlen(string); i++) {
        EXPECT_EQ(memory[0x100 + i], string[i]);
    }
}

TEST(memory_tests, load_instruction) {
    uint32_t instruction = 0x12345678;
    load_instruction(0x100, instruction);
    EXPECT_EQ(*(uint32_t*)&memory[0x100], instruction);
}

TEST(memory_tests, load_instructions_from_txt) {
    load_instructions_from_txt("test/test_program.txt");
    EXPECT_EQ(*(uint32_t*)&memory[MEMORY_SIZE-TEXT_MEMORY_SIZE+1], 0x12345678);
    EXPECT_EQ(*(uint32_t*)&memory[MEMORY_SIZE-TEXT_MEMORY_SIZE+4+1], 0x87654321);
}

TEST(memory_tests, load_instructions_from_invalid_txt) {
    // TODO: Test with a mock
    // load_instructions_from_txt("test/foo.txt");
}
