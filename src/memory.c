#include "memory.h"
#include <string.h>

uint32_t registers[32];
uint8_t memory[MEMORY_SIZE];

void reset_registers_and_memory() {
    memset(registers, 0, sizeof(registers));
    memset(memory, 0, sizeof(memory));
}