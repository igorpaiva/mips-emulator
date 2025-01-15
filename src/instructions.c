#include "instructions.h"

void decode_funct(uint8_t funct, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t shamt) {
    switch (funct) {
    case 0x00:
        sll(rd, rt, shamt);
        break;
    case 0x02:
        srl(rd, rt, shamt);
        break;
    case 0x08:
        jr(rs);
        break;
    case 0x0C:
        syscall();
        break;
    case 0x20:
        add(rd, rs, rt);
        break;
    case 0x21:
        addu(rd, rs, rt);
        break;
    case 0x22:
        sub(rd, rs, rt);
        break;
    case 0x23:
        subu(rd, rs, rt);
        break;
    case 0x24:
        and(rd, rs, rt);
        break;
    case 0x25:
        or(rd, rs, rt);
        break;
    case 0x27:
        nor(rd, rs, rt);
        break;
    case 0x2A:
        slt(rd, rs, rt);
        break;
    case 0x2B:
        sltu(rd, rs, rt);
        break;
    default:
        log_error("Unknown or not implemented instruction with funct = %d\n", funct);
        break;
    }
}

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
            decode_funct(funct, rs, rt, rd, shamt);
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
        case 0x9:  // addiu
            addiu(rt, rs, immediate);
            break;
        case 0xC:  // andi
            andi(rt, rs, immediate);
            break;
        case 0x1A:  // slti
            slti(rt, rs, immediate);
            break;
        case 0x1B:  // sltiu
            sltiu(rt, rs, immediate);
            break;
        case 0x20:  // lb
            lb(rt, rs, immediate);
            break;
        case 0x24:  // lbu
            lbu(rt, rs, immediate);
            break;
        case 0x21:  // lh
            lh(rt, rs, immediate);
            break;
        case 0x25:  // lhu
            lhu(rt, rs, immediate);
            break;
        case 0x23:  // lw
            lw(rt, rs, immediate);
            break;
        case 0x28:  // sb
            sb(rt, rs, immediate);
            break;
        case 0x29:  // sh
            sh(rt, rs, immediate);
            break;
        case 0x2B:  // sw
            sw(rt, rs, immediate);
            break;
        case 0x2:  // j
            j(instruction & 0x3FFFFFF);
            break;
        case 0x3:  // jal
            jal(instruction & 0x3FFFFFF);
            break;
        default:
            log_error("Unknown or not implemented instruction at pc = %d\n", pc);
            break;
    }
}

// Arithmetic and Logical Instructions

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
    registers[rt] = ((int32_t)registers[rs] < (int32_t)immediate)? 1 : 0;
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