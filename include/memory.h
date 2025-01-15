#ifndef MEMORY_H
#define MEMORY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "log.h"

#define MEMORY_SIZE 1024
#define TEXT_MEMORY_SIZE 0x0FF
#define PC_START TEXT_MEMORY_SIZE+1

typedef enum {
    zero,   // $zero
    at,         // $at
    v0, v1,     // $v0-$v1
    a0, a1, a2, a3,  // $a0-$a3
    t0, t1, t2, t3, t4, t5, t6, t7,  // $t0-$t7
    s0, s1, s2, s3, s4, s5, s6, s7,  // $s0-$s7
    t8, t9,     // $t8-$t9
    k0, k1,     // $k0-$k1
    gp,         // $gp
    sp,         // $sp
    fp,         // $fp
    ra,         // $ra
    hi,    // HI register
    lo          // LO register
} mips_register;

extern uint32_t registers[34];
extern uint8_t data_memory[MEMORY_SIZE];
extern uint8_t memory[MEMORY_SIZE];
extern uint32_t pc;

void reset_registers_and_memory();
void reset_pc();

void load_string_to_memory(const char *string, uint32_t address);
void load_instruction(uint32_t address, uint32_t instruction);
void load_instructions_from_txt(const char *filename);

#endif