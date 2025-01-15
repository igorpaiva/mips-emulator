#include "rktest/rktest.h"
#include "memory.h"
#include "instructions.h"

TEST_SETUP(instruction_tests) {
    reset_registers_and_memory();
}

TEST(instruction_tests, test_add) {
    int rd = t0;
    int rs = t1;
    int rt = t2;
    registers[rs] = 0x1234;
    registers[rt] = 0x5678;
    add(rd, rs, rt);
    EXPECT_EQ(registers[rd], 0x68AC);
}

TEST(instruction_tests, test_add_negative_nums) {
    int rd = t0;
    int rs = t1;
    int rt = t2;
    registers[rs] = 0xFFFFFFFE; // -2
    registers[rt] = 0xFFFFFFFC; // -4
    add(rd, rs, rt); // -2 + -4 = -6
    EXPECT_EQ(registers[rd], 0xFFFFFFFA);

    registers[rs] = 0xFFFFFFF5; // -11
    registers[rt] = 0xFFFFFFFC; // -4
    add(rd, rs, rt); // -11 + -4 = -15
    EXPECT_EQ(registers[rd], 0xFFFFFFF1);
}

TEST(instruction_tests, test_addu) {
    int rd = t0;
    int rs = t1;
    int rt = t2;
    registers[rs] = 0x1234;
    registers[rt] = 0x5678;
    addu(rd, rs, rt);
    EXPECT_EQ(registers[rd], 0x68AC);
}

TEST(instruction_tests, test_addu_negative_nums) {
    int rd = t0;
    int rs = t1;
    int rt = t2;
    registers[rs] = 0xFFFFFFF5; // -11
    registers[rt] = 0x3; // 3
    addu(rd, rs, rt); // -11 + 3 = -8
    EXPECT_NE(registers[rd], -15);
    EXPECT_EQ(registers[rd], 0xFFFFFFF8);
}

TEST(instruction_tests, test_lui) {
    int rt = t0;
    lui(rt, 0x1234);
    EXPECT_EQ(registers[rt], 0x12340000);
}

TEST(instruction_tests, test_ori) {
    int rt = t0;
    int rs = t1;
    lui(rs, 0x1234);
    ori(rt, rs, 0x5678);
    EXPECT_EQ(registers[rt], 0x12345678);
}

TEST(instruction_tests, test_addi) {
    int rt = t0;
    int rs = t1;
    registers[rs] = 0x1234;
    addi(rt, rs, 0x5678);
    EXPECT_EQ(registers[rt], 0x68AC);
}

TEST(instruction_tests, test_addi_negative_nums) {
    int rt = t0;
    int rs = t1;
    registers[rs] = 0xFFFFFFFE; // -2
    addi(rt, rs, 0x3); // -2 + 3 = 1
    EXPECT_EQ(registers[rt], 0x1);

    registers[rs] = 0xFFFFFFF5; // -11
    addi(rt, rs, (int32_t)0xFFFFFFFC);   // -11 + -4 = -15
    EXPECT_EQ(registers[rt], -15);
    EXPECT_NE(registers[rt], 0xFFFFFFF8);
}

TEST(instruction_tests, test_addiu) {
    int rt = t0;
    int rs = t1;
    registers[rs] = 0x1234;
    addiu(rt, rs, 0x5678);
    EXPECT_EQ(registers[rt], 0x68AC);
}

TEST(instruction_tests, test_addiu_negative_nums) {
    int rt = t0;
    int rs = t1;
    registers[rs] = 0xFFFFFFF5; // -11
    addiu(rt, rs, 0x3); // -11 + 3 = -8
    EXPECT_NE(registers[rt], -15);
    EXPECT_EQ(registers[rt], 0xFFFFFFF8);
}

TEST(instruction_tests, test_andi) {
    int rt = t0;
    int rs = t1;
    ori(rs, zero, 0x1234);
    andi(rt, rs, 0x5678);
    EXPECT_EQ(registers[rt], 0x1234 & 0x5678);
}

TEST(instruction_tests, test_slti) {
    int rt = t0;
    int rs = t1;
    registers[rs] = 0x1234;
    slti(rt, rs, 0x5678);
    EXPECT_EQ(registers[rt], 0x1234 < 0x5678);
}

TEST(instruction_tests, test_slti_negative_nums) {
    int rt = t0;
    int rs = t1;
    registers[rs] = 0xFFFFFFFE; // -2
    slti(rt, rs, 0x3); // -2 < 3 = 1
    EXPECT_EQ(registers[rt], 1);

    registers[rs] = 0xFFFFFFF5; // -11
    slti(rt, rs, (int32_t)0xFFFFFFFC);   // -11 < -4 = 1
    EXPECT_EQ(registers[rt], 1);
}

TEST(instruction_tests, test_sltiu){
    int rt = t0;
    int rs = t1;
    registers[rs] = 0xFFFFFFF5; // not -11
    sltiu(rt, rs, 0x3); // 0xFFFFFFF5 < 3 = 0
    EXPECT_EQ(registers[rt], 0);

    registers[rs] = 0xFFFFFFFC; // not -4
    sltiu(rt, rs, (int32_t)0xFFFFFFF5);   // 0xFFFFFFFC < 0xFFFFFFF5 = 0
    EXPECT_EQ(registers[rt], 0);
}
