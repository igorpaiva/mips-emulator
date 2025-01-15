#include "rktest/rktest.h"
#include "memory.h"
#include "instructions.h"

TEST_SETUP(decode_tests) {
    reset_registers_and_memory();
}

TEST(decode_tests, test_decode_unknown_funct){
    uint8_t opcode = 0;
    uint8_t rd = 0;
    uint8_t rs = 0;
    uint8_t rt = 0;
    uint8_t shamt = 0;
    uint8_t funct = 0x3F;

    uint32_t instruction = (opcode << 26) | (rs << 21) | (rt << 16) | (rd << 11) | (shamt << 6) | funct;
    decode_instruction(instruction);
    // TODO: Test if the error was logged
}

TEST(decode_tests, test_decode_unknown_opcode){
    uint8_t opcode = 0x3F;
    uint8_t rd = 0;
    uint8_t rs = 0;
    uint8_t rt = 0;
    uint8_t shamt = 0;
    uint8_t funct = 0;

    uint32_t instruction = (opcode << 26) | (rs << 21) | (rt << 16) | (rd << 11) | (shamt << 6) | funct;
    decode_instruction(instruction);
    // TODO: Test if the error was logged
}

TEST(decode_tests, test_decode_instruction_sll){
    uint8_t opcode = 0;
    uint8_t rd = t0;
    uint8_t rs = t1;
    uint8_t rt = t2;
    uint8_t shamt = 4;
    uint8_t funct = 0x00;

    registers[rt] = 0x1234;

    uint32_t instruction = (opcode << 26) | (rs << 21) | (rt << 16) | (rd << 11) | (shamt << 6) | funct;
    decode_instruction(instruction);
    EXPECT_EQ(registers[rd], 0x1234 << 4);
}

TEST(decode_tests, test_decode_instruction_srl){
    uint8_t opcode = 0;
    uint8_t rd = t0;
    uint8_t rs = t1;
    uint8_t rt = t2;
    uint8_t shamt = 4;
    uint8_t funct = 0x02;

    registers[rt] = 0x1234;

    uint32_t instruction = (opcode << 26) | (rs << 21) | (rt << 16) | (rd << 11) | (shamt << 6) | funct;
    decode_instruction(instruction);
    EXPECT_EQ(registers[rd], 0x1234 >> 4);
}

TEST(decode_tests, test_decode_instruction_jr){
    uint8_t opcode = 0;
    uint8_t rd = 0;
    uint8_t rs = t1;
    uint8_t rt = 0;
    uint8_t shamt = 0;
    uint8_t funct = 0x08;

    registers[rs] = 0x1234;

    uint32_t instruction = (opcode << 26) | (rs << 21) | (rt << 16) | (rd << 11) | (shamt << 6) | funct;
    decode_instruction(instruction);
    EXPECT_EQ(pc, 0x1234);
}

TEST(decode_tests, test_decode_instruction_syscall){
    uint8_t opcode = 0;
    uint8_t rd = 0;
    uint8_t rs = 0;
    uint8_t rt = 0;
    uint8_t shamt = 0;
    uint8_t funct = 0x0C;

    registers[v0] = 4;
    registers[a0] = 8;
    char *string = "Hello, World!";
    load_string_to_memory(string, registers[a0]);

    uint32_t instruction = (opcode << 26) | (rs << 21) | (rt << 16) | (rd << 11) | (shamt << 6) | funct;
    decode_instruction(instruction);
    // TODO: Test if the string was logged
}

TEST(decode_tests, test_decode_instruction_add){
    uint8_t opcode = 0;
    uint8_t rd = t0;
    uint8_t rs = t1;
    uint8_t rt = t2;
    uint8_t shamt = 0;
    uint8_t funct = 0x20;

    registers[rs] = 0x1234;
    registers[rt] = 0x5678;

    uint32_t instruction = (opcode << 26) | (rs << 21) | (rt << 16) | (rd << 11) | (shamt << 6) | funct;
    decode_instruction(instruction);
    EXPECT_EQ(registers[rd], 0x68AC);
}

TEST(decode_tests, test_decode_instruction_addu){
    uint8_t opcode = 0;
    uint8_t rd = t0;
    uint8_t rs = t1;
    uint8_t rt = t2;
    uint8_t shamt = 0;
    uint8_t funct = 0x21;

    registers[rs] = 0x1234;
    registers[rt] = 0x5678;

    uint32_t instruction = (opcode << 26) | (rs << 21) | (rt << 16) | (rd << 11) | (shamt << 6) | funct;
    decode_instruction(instruction);
    EXPECT_EQ(registers[rd], 0x68AC);
}

TEST(decode_tests, test_decode_instruction_sub){
    uint8_t opcode = 0;
    uint8_t rd = t0;
    uint8_t rs = t1;
    uint8_t rt = t2;
    uint8_t shamt = 0;
    uint8_t funct = 0x22;

    registers[rt] = 0x1234;
    registers[rs] = 0x5678;

    uint32_t instruction = (opcode << 26) | (rs << 21) | (rt << 16) | (rd << 11) | (shamt << 6) | funct;
    decode_instruction(instruction);
    EXPECT_EQ(registers[rd], 0x4444);
}

TEST(decode_tests, test_decode_instruction_subu){
    uint8_t opcode = 0;
    uint8_t rd = t0;
    uint8_t rs = t1;
    uint8_t rt = t2;
    uint8_t shamt = 0;
    uint8_t funct = 0x23;

    registers[rt] = 0x1234;
    registers[rs] = 0x5678;

    uint32_t instruction = (opcode << 26) | (rs << 21) | (rt << 16) | (rd << 11) | (shamt << 6) | funct;
    decode_instruction(instruction);
    EXPECT_EQ(registers[rd], 0x4444);
}

TEST(decode_tests, test_decode_instruction_and){
    uint8_t opcode = 0;
    uint8_t rd = t0;
    uint8_t rs = t1;
    uint8_t rt = t2;
    uint8_t shamt = 0;
    uint8_t funct = 0x24;

    registers[rs] = 0x1234;
    registers[rt] = 0x5678;

    uint32_t instruction = (opcode << 26) | (rs << 21) | (rt << 16) | (rd << 11) | (shamt << 6) | funct;
    decode_instruction(instruction);
    EXPECT_EQ(registers[rd], 0x1234 & 0x5678);
}

TEST(decode_tests, test_decode_instruction_or){
    uint8_t opcode = 0;
    uint8_t rd = t0;
    uint8_t rs = t1;
    uint8_t rt = t2;
    uint8_t shamt = 0;
    uint8_t funct = 0x25;

    registers[rs] = 0x1234;
    registers[rt] = 0x5678;

    uint32_t instruction = (opcode << 26) | (rs << 21) | (rt << 16) | (rd << 11) | (shamt << 6) | funct;
    decode_instruction(instruction);
    EXPECT_EQ(registers[rd], 0x1234 | 0x5678);
}

TEST(decode_tests, test_decode_instruction_nor){
    uint8_t opcode = 0;
    uint8_t rd = t0;
    uint8_t rs = t1;
    uint8_t rt = t2;
    uint8_t shamt = 0;
    uint8_t funct = 0x27;

    registers[rs] = 0x1234;
    registers[rt] = 0x5678;

    uint32_t instruction = (opcode << 26) | (rs << 21) | (rt << 16) | (rd << 11) | (shamt << 6) | funct;
    decode_instruction(instruction);
    EXPECT_EQ(registers[rd], ~(0x1234 | 0x5678));
}

TEST(decode_tests, test_decode_instruction_slt){
    uint8_t opcode = 0;
    uint8_t rd = t0;
    uint8_t rs = t1;
    uint8_t rt = t2;
    uint8_t shamt = 0;
    uint8_t funct = 0x2A;

    registers[rs] = 0x1234;
    registers[rt] = 0x5678;

    uint32_t instruction = (opcode << 26) | (rs << 21) | (rt << 16) | (rd << 11) | (shamt << 6) | funct;
    decode_instruction(instruction);
    EXPECT_EQ(registers[rd], 0x1234 < 0x5678);
}

TEST(decode_tests, test_decode_instruction_sltu){
    uint8_t opcode = 0;
    uint8_t rd = t0;
    uint8_t rs = t1;
    uint8_t rt = t2;
    uint8_t shamt = 0;
    uint8_t funct = 0x2B;

    registers[rs] = 0xFFFFFFF5;
    registers[rt] = 0x3;

    uint32_t instruction = (opcode << 26) | (rs << 21) | (rt << 16) | (rd << 11) | (shamt << 6) | funct;
    decode_instruction(instruction);
}
