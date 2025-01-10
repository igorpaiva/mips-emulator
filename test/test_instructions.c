#include "rktest/rktest.h"
#include "memory.h"
#include "instructions.h"

// Test case: LUI instruction
TEST(instruction_tests, test_lui) {
    reset_registers_and_memory();
    int rt = 8; // $t0
    lui(rt, 0x1234);
    EXPECT_EQ(registers[rt], 0x12340000);
}

// Test case: ORI instruction
TEST(instruction_tests, test_ori) {
    reset_registers_and_memory();
    int rt = 8; // $t0
    int rs = 9; // $t1
    lui(rs, 0x1234);
    ori(rt, rs, 0x5678);
    EXPECT_EQ(registers[rt], 0x12345678);
}

// Test case: ADDI instruction
TEST(instruction_tests, test_addi) {
    reset_registers_and_memory();
    int rt = 8; // $t0
    int rs = 9; // $t1
    registers[rs] = 0x1234;
    addi(rt, rs, 0x5678);
    EXPECT_EQ(registers[rt], 0x68AC);
}
