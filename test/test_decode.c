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
    store_string_in_memory(string, registers[a0]);

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

TEST(decode_tests, test_decode_instruction_lui){
    uint8_t opcode = 0xF;
    uint8_t rs = 0;
    uint8_t rt = t0;

    int16_t immediate = 0x1234;

    uint32_t instruction = (opcode << 26) | (rs << 21) | (rt << 16) | (immediate & 0xFFFF);
    decode_instruction(instruction);
    EXPECT_EQ(registers[rt], 0x12340000);
}

TEST(decode_tests, test_decode_instruction_ori){
    uint8_t opcode = 0xD;
    uint8_t rs = t1;
    uint8_t rt = t0;

    int16_t immediate = 0x5678;

    registers[rs] = 0x1234;

    uint32_t instruction = (opcode << 26) | (rs << 21) | (rt << 16) | (immediate & 0xFFFF);
    decode_instruction(instruction);
    EXPECT_EQ(registers[rt], 0x1234 | 0x5678);
}

TEST(decode_tests, test_decode_instruction_addi){
    uint8_t opcode = 0x8;
    uint8_t rs = t1;
    uint8_t rt = t0;

    int16_t immediate = 0x5678;

    registers[rs] = 0x1234;

    uint32_t instruction = (opcode << 26) | (rs << 21) | (rt << 16) | (immediate & 0xFFFF);
    decode_instruction(instruction);
    EXPECT_EQ(registers[rt], 0x1234 + 0x5678);
}

TEST(decode_tests, test_decode_instruction_addiu){
    uint8_t opcode = 0x9;
    uint8_t rs = t1;
    uint8_t rt = t0;

    int16_t immediate = 0x5678;

    registers[rs] = 0x1234;

    uint32_t instruction = (opcode << 26) | (rs << 21) | (rt << 16) | (immediate & 0xFFFF);
    decode_instruction(instruction);
    EXPECT_EQ(registers[rt], 0x1234 + 0x5678);
}

TEST(decode_tests, test_decode_instruction_andi){
    uint8_t opcode = 0xC;
    uint8_t rs = t1;
    uint8_t rt = t0;

    int16_t immediate = 0x5678;

    registers[rs] = 0x1234;

    uint32_t instruction = (opcode << 26) | (rs << 21) | (rt << 16) | (immediate & 0xFFFF);
    decode_instruction(instruction);
    EXPECT_EQ(registers[rt], 0x1234 & 0x5678);
}

TEST(decode_tests, test_decode_instruction_slti){
    uint8_t opcode = 0x1A;
    uint8_t rs = t1;
    uint8_t rt = t0;

    int16_t immediate = 0x5678;

    registers[rs] = 0x1234;

    uint32_t instruction = (opcode << 26) | (rs << 21) | (rt << 16) | (immediate & 0xFFFF);
    decode_instruction(instruction);
    EXPECT_EQ(registers[rt], 0x1234 < 0x5678);
}

TEST(decode_tests, test_decode_instruction_sltiu){
    uint8_t opcode = 0x1B;
    uint8_t rs = t1;
    uint8_t rt = t0;

    int16_t immediate = 0x5678;

    registers[rs] = 0xFFFFFFF5;

    uint32_t instruction = (opcode << 26) | (rs << 21) | (rt << 16) | (immediate & 0xFFFF);
    decode_instruction(instruction);
}

TEST(decode_tests, test_decode_instruction_lb){
    uint8_t opcode = 0x20;
    uint8_t rs = a0;
    uint8_t rt = t0;

    int16_t immediate = 20;

    registers[rs] = 0xC;

    store_string_in_memory("Test", registers[rs] + immediate);

    uint32_t instruction = (opcode << 26) | (rs << 21) | (rt << 16) | (immediate & 0xFFFF);
    decode_instruction(instruction);
    EXPECT_EQ(registers[rt], 'T');
}

TEST(decode_tests, test_decode_instruction_lbu){
    uint8_t opcode = 0x24;
    uint8_t rs = a0;
    uint8_t rt = t0;

    int16_t immediate = 20;

    registers[rs] = 0xC;

    store_string_in_memory("Test", registers[rs] + immediate);

    uint32_t instruction = (opcode << 26) | (rs << 21) | (rt << 16) | (immediate & 0xFFFF);
    decode_instruction(instruction);
    EXPECT_EQ(registers[rt], 'T');
}

TEST(decode_tests, test_decode_instruction_lh){
    uint8_t opcode = 0x21;
    uint8_t rs = a0;
    uint8_t rt = t0;

    int16_t immediate = 20;

    registers[rs] = 0xC;

    store_string_in_memory("Test", registers[rs] + immediate);

    uint32_t instruction = (opcode << 26) | (rs << 21) | (rt << 16) | (immediate & 0xFFFF);
    decode_instruction(instruction);
    EXPECT_EQ(registers[rt], 'T' | ('e' << 8));
}

TEST(decode_tests, test_decode_instruction_lhu){
    uint8_t opcode = 0x25;
    uint8_t rs = a0;
    uint8_t rt = t0;

    int16_t immediate = 20;

    registers[rs] = 0xC;

    store_string_in_memory("Test", registers[rs] + immediate);

    uint32_t instruction = (opcode << 26) | (rs << 21) | (rt << 16) | (immediate & 0xFFFF);
    decode_instruction(instruction);
    EXPECT_EQ(registers[rt], 'T' | ('e' << 8));
}

TEST(decode_tests, test_decode_instruction_lw){
    uint8_t opcode = 0x23;
    uint8_t rs = a0;
    uint8_t rt = t0;

    int16_t immediate = 20;

    registers[rs] = 0xC;

    store_string_in_memory("Test", registers[rs] + immediate);

    uint32_t instruction = (opcode << 26) | (rs << 21) | (rt << 16) | (immediate & 0xFFFF);
    decode_instruction(instruction);
    EXPECT_EQ(registers[rt], 'T' | ('e' << 8) | ('s' << 16) | ('t' << 24));
}

TEST(decode_tests, test_decode_instruction_sb){
    uint8_t opcode = 0x28;
    uint8_t rs = a0;
    uint8_t rt = t0;

    int16_t immediate = 20;

    registers[rs] = 0xC;
    registers[rt] = 'T';

    uint32_t instruction = (opcode << 26) | (rs << 21) | (rt << 16) | (immediate & 0xFFFF);
    decode_instruction(instruction);
    EXPECT_EQ(memory[registers[rs] + immediate], 'T');
}

TEST(decode_tests, test_decode_instruction_sh){
    uint8_t opcode = 0x29;
    uint8_t rs = a0;
    uint8_t rt = t0;

    int16_t immediate = 20;

    registers[rs] = 0xC;
    registers[rt] = 'T' | ('e' << 8);

    uint32_t instruction = (opcode << 26) | (rs << 21) | (rt << 16) | (immediate & 0xFFFF);
    decode_instruction(instruction);
    EXPECT_EQ(*(uint16_t*)&memory[registers[rs] + immediate], 'T' | ('e' << 8));
}

TEST(decode_tests, test_decode_instruction_sw){
    uint8_t opcode = 0x2B;
    uint8_t rs = a0;
    uint8_t rt = t0;

    int16_t immediate = 20;

    registers[rs] = 0xC;
    registers[rt] = 'T' | ('e' << 8) | ('s' << 16) | ('t' << 24);

    uint32_t instruction = (opcode << 26) | (rs << 21) | (rt << 16) | (immediate & 0xFFFF);
    decode_instruction(instruction);
    EXPECT_EQ(*(uint32_t*)&memory[registers[rs] + immediate], 'T' | ('e' << 8) | ('s' << 16) | ('t' << 24));
}

TEST(decode_tests, test_decode_instruction_j){
    uint8_t opcode = 0x2;
    uint32_t target = 0x40;

    uint32_t instruction = (opcode << 26) | (target & 0x3FFFFFF);
    decode_instruction(instruction);
    EXPECT_EQ(pc, 0x40 << 2);
}

TEST(decode_tests, test_decode_instruction_jal){
    uint8_t opcode = 0x3;
    uint32_t target = 0x40;

    uint32_t instruction = (opcode << 26) | (target & 0x3FFFFFF);
    decode_instruction(instruction);
    EXPECT_EQ(pc, 0x40 << 2);
    EXPECT_EQ(registers[31], 0x104);
}
