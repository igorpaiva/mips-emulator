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

// Last two registers are the HI and LO registers
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