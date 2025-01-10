#include "instructions.h"

// Arithmetic and Logical Instructions

void decode_instruction(uint32_t instruction) {

    uint8_t opcode = (instruction >> 26) & 0x3F;
    uint8_t rs = (instruction >> 21) & 0x1F;
    uint8_t rt = (instruction >> 16) & 0x1F;
    uint8_t rd = (instruction >> 11) & 0x1F;
    uint8_t shamt = (instruction >> 6) & 0x1F;
    uint8_t funct = instruction & 0x3F;
    int16_t immediate = instruction & 0xFFFF;

    switch (opcode) {
        
        case 0x00:
            if (funct == 0x0C) {  // syscall
                syscall();
            }
            break;
        case 0xF:  // lui
            lui(rt, immediate);
            break;
        case 0xD:  // ori
            ori(rt, rs, immediate);
            break;
        case 0x8:  // addi
            addi(rt, rs, immediate);
            break;
        default:
            log_error("Unknown instruction at pc = %d\n", pc);
            break;
    }
}

void add(uint8_t rd, uint8_t rs, uint8_t rt) {
    registers[rd] = registers[rs] + registers[rt];
}

void addu(uint8_t rd, uint8_t rs, uint8_t rt) {
    registers[rd] = registers[rs] + registers[rt];
}

void addi(uint8_t rt, uint8_t rs, int16_t immediate) {
    registers[rt] = registers[rs] + immediate;
}

void addiu(uint8_t rt, uint8_t rs, int16_t immediate) {
    registers[rt] = registers[rs] + immediate;
}

void and(uint8_t rd, uint8_t rs, uint8_t rt) {
    registers[rd] = registers[rs] & registers[rt];
}

void andi(uint8_t rt, uint8_t rs, int16_t immediate) {
    registers[rt] = registers[rs] & (uint16_t)immediate;
}

void div_reg(uint8_t rs, uint8_t rt) {
    registers[32] = registers[rs] / registers[rt];
    registers[33] = registers[rs] % registers[rt];
}

void divu(uint8_t rs, uint8_t rt) {
    registers[32] = registers[rs] / registers[rt];
    registers[33] = registers[rs] % registers[rt];
}

void mult(uint8_t rs, uint8_t rt) {
    registers[32] = registers[rs] * registers[rt];
}

void multu(uint8_t rs, uint8_t rt) {
    registers[32] = registers[rs] * registers[rt];
}

void nor(uint8_t rd, uint8_t rs, uint8_t rt) {
    registers[rd] = ~(registers[rs] | registers[rt]);
}

void or(uint8_t rd, uint8_t rs, uint8_t rt) {
    registers[rd] = registers[rs] | registers[rt];
}

void ori(uint8_t rt, uint8_t rs, int16_t immediate) {
    registers[rt] = registers[rs] | (uint16_t)immediate;
}

void sll(uint8_t rd, uint8_t rt, uint8_t shamt) {
    registers[rd] = registers[rt] << shamt;
}

void sllv(uint8_t rd, uint8_t rt, uint8_t rs) {
    registers[rd] = registers[rt] << registers[rs];
}

void sra(uint8_t rd, uint8_t rt, uint8_t shamt) {
    registers[rd] = registers[rt] >> shamt;
}

void srav(uint8_t rd, uint8_t rt, uint8_t rs) {
    registers[rd] = registers[rt] >> registers[rs];
}

void srl(uint8_t rd, uint8_t rt, uint8_t shamt) {
    registers[rd] = registers[rt] >> shamt;
}

void srlv(uint8_t rd, uint8_t rt, uint8_t rs) {
    registers[rd] = registers[rt] >> registers[rs];
}

void sub(uint8_t rd, uint8_t rs, uint8_t rt) {
    registers[rd] = registers[rs] - registers[rt];
}

void subu(uint8_t rd, uint8_t rs, uint8_t rt) {
    registers[rd] = registers[rs] - registers[rt];
}

void xor(uint8_t rd, uint8_t rs, uint8_t rt) {
    registers[rd] = registers[rs] ^ registers[rt];
}

void xori(uint8_t rt, uint8_t rs, int16_t immediate) {
    registers[rt] = registers[rs] ^ (uint16_t)immediate;
}

// Comparison Instructions

void slt(uint8_t rd, uint8_t rs, uint8_t rt) {
    registers[rd] = (registers[rs] < registers[rt])? 1 : 0;
}

void sltu(uint8_t rd, uint8_t rs, uint8_t rt) {
    registers[rd] = (registers[rs] < registers[rt])? 1 : 0;
}

void slti(uint8_t rt, uint8_t rs, int16_t immediate) {
    registers[rt] = (registers[rs] < (uint32_t)immediate)? 1 : 0;
}

void sltiu(uint8_t rt, uint8_t rs, int16_t immediate) {
    registers[rt] = (registers[rs] < (uint32_t)immediate)? 1 : 0;
}

// Branch Instructions

void beq(uint8_t rs, uint8_t rt, int16_t immediate) {
    if (registers[rs] == registers[rt]) {
        registers[32] = pc + 4;
        pc += immediate << 2;
    }
}

void bne(uint8_t rs, uint8_t rt, int16_t immediate) {
    if (registers[rs] != registers[rt]) {
        registers[32] = pc + 4;
        pc += immediate << 2;
    }
}

void bgtz(uint8_t rs, int16_t immediate) {
    if (registers[rs] > 0) {
        registers[32] = pc + 4;
        pc += immediate << 2;
    }
}

void blez(uint8_t rs, int16_t immediate) {
    if (registers[rs] <= 0) {
        registers[32] = pc + 4;
        pc += immediate << 2;
    }
}

// Jump Instructions

void j(uint32_t target) {
    pc = (pc & 0xF0000000) | (target << 2);
}

void jal(uint32_t target) {
    registers[31] = pc + 4;
    pc = (pc & 0xF0000000) | (target << 2);
}

void jr(uint8_t rs) {
    pc = registers[rs];
}

void jalr(uint8_t rs, uint8_t rd) {
    registers[rd] = pc + 4;
    pc = registers[rs];
}

// Load Instructions

void lb(uint8_t rt, uint8_t rs, int16_t immediate) {
    registers[rt] = memory[registers[rs] + immediate];
}

void lbu(uint8_t rt, uint8_t rs, int16_t immediate) {
    registers[rt] = memory[registers[rs] + immediate];
}

void lh(uint8_t rt, uint8_t rs, int16_t immediate) {
    registers[rt] = *(uint16_t*)&memory[registers[rs] + immediate];
}

void lhu(uint8_t rt, uint8_t rs, int16_t immediate) {
    registers[rt] = *(uint16_t*)&memory[registers[rs] + immediate];
}

void lw(uint8_t rt, uint8_t rs, int16_t immediate) {
    registers[rt] = *(uint32_t*)&memory[registers[rs] + immediate];
}

void lui(uint8_t rt, int16_t immediate) {
    registers[rt] = immediate << 16;
}

// Store Instructions

void sb(uint8_t rt, uint8_t rs, int16_t immediate) {
    memory[registers[rs] + immediate] = registers[rt];
}

void sh(uint8_t rt, uint8_t rs, int16_t immediate) {
    *(uint16_t*)&memory[registers[rs] + immediate] = registers[rt];
}

void sw(uint8_t rt, uint8_t rs, int16_t immediate) {
    *(uint32_t*)&memory[registers[rs] + immediate] = registers[rt];
}