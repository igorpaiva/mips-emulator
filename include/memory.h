#ifndef MEMORY_H
#define MEMORY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MEMORY_SIZE 1024

// Last two registers are the HI and LO registers
extern uint32_t registers[34];
extern uint8_t memory[MEMORY_SIZE];
extern uint32_t pc;

void reset_registers_and_memory();

#endif