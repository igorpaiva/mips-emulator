#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

#define MEMORY_SIZE 1024

extern uint32_t registers[32];
extern uint8_t memory[MEMORY_SIZE];

void reset_registers_and_memory();

#endif