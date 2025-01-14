#include "rktest/rktest.h"
#include "memory.h"
#include "instructions.h"

TEST_SETUP(instruction_tests) {
    reset_registers_and_memory();
}

TEST(instruction_tests, test_lui) {
    int rt = 8; // $t0
    lui(rt, 0x1234);
    EXPECT_EQ(registers[rt], 0x12340000);
}


TEST(instruction_tests, test_ori) {
    int rt = 8; // $t0
    int rs = 9; // $t1
    lui(rs, 0x1234);
    ori(rt, rs, 0x5678);
    EXPECT_EQ(registers[rt], 0x12345678);
}

TEST(instruction_tests, test_addi) {
    int rt = 8; // $t0
    int rs = 9; // $t1
    registers[rs] = 0x1234;
    addi(rt, rs, 0x5678);
    EXPECT_EQ(registers[rt], 0x68AC);
}
