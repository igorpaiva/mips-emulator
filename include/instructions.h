#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "memory.h"

void add(uint8_t rd, uint8_t rs, uint8_t rt);
void addu(uint8_t rd, uint8_t rs, uint8_t rt);
void addi(uint8_t rt, uint8_t rs, int16_t immediate);
void addiu(uint8_t rt, uint8_t rs, int16_t immediate);
void and(uint8_t rd, uint8_t rs, uint8_t rt);
void andi(uint8_t rt, uint8_t rs, int16_t immediate);
void div_reg(uint8_t rs, uint8_t rt); //TODO: find a better name, as div conflicts with a function in stdlib.h
void divu(uint8_t rs, uint8_t rt);
void mult(uint8_t rs, uint8_t rt);
void multu(uint8_t rs, uint8_t rt);
void nor(uint8_t rd, uint8_t rs, uint8_t rt);
void or(uint8_t rd, uint8_t rs, uint8_t rt);
void ori(uint8_t rt, uint8_t rs, int16_t immediate);
void sll(uint8_t rd, uint8_t rt, uint8_t shamt);
void sllv(uint8_t rd, uint8_t rt, uint8_t rs);
void sra(uint8_t rd, uint8_t rt, uint8_t shamt);
void srav(uint8_t rd, uint8_t rt, uint8_t rs);
void srl(uint8_t rd, uint8_t rt, uint8_t shamt);
void srlv(uint8_t rd, uint8_t rt, uint8_t rs);
void sub(uint8_t rd, uint8_t rs, uint8_t rt);
void subu(uint8_t rd, uint8_t rs, uint8_t rt);
void xor(uint8_t rd, uint8_t rs, uint8_t rt);
void xori(uint8_t rt, uint8_t rs, int16_t immediate);
void slt(uint8_t rd, uint8_t rs, uint8_t rt);
void sltu(uint8_t rd, uint8_t rs, uint8_t rt);
void slti(uint8_t rt, uint8_t rs, int16_t immediate);
void sltiu(uint8_t rt, uint8_t rs, int16_t immediate);
void beq(uint8_t rs, uint8_t rt, int16_t immediate);
void bne(uint8_t rs, uint8_t rt, int16_t immediate);
void bgtz(uint8_t rs, int16_t immediate);
void blez(uint8_t rs, int16_t immediate);
void j(uint32_t target);
void jal(uint32_t target);
void jr(uint8_t rs);
void jalr(uint8_t rs, uint8_t rd);
void lb(uint8_t rt, uint8_t rs, int16_t immediate);
void lbu(uint8_t rt, uint8_t rs, int16_t immediate);
void lh(uint8_t rt, uint8_t rs, int16_t immediate);
void lhu(uint8_t rt, uint8_t rs, int16_t immediate);
void lw(uint8_t rt, uint8_t rs, int16_t immediate);
void lui(uint8_t rt, int16_t immediate);
void sb(uint8_t rt, uint8_t rs, int16_t immediate);
void sh(uint8_t rt, uint8_t rs, int16_t immediate);
void sw(uint8_t rt, uint8_t rs, int16_t immediate);

#endif