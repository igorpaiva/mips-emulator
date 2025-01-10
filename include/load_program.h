#ifndef LOAD_PROGRAM_H
#define LOAD_PROGRAM_H

#include "memory.h"

void load_instruction(uint32_t address, uint32_t instruction);
void load_instructions_from_txt(const char *filename);

#endif