#include "memory.h"
#include <string.h>

uint32_t registers[34];
uint8_t memory[MEMORY_SIZE];
uint32_t pc;

// Reset functions

void reset_registers_and_memory() {
    memset(registers, 0, sizeof(registers));
    memset(memory, 0, sizeof(memory));
}

void reset_pc() {
    //(TODO: refactor memory division to a more appropriate approach)
    pc = PC_START; // PC starts at 0x100, from 0x000 to 0x0FF is the text section
}

// Load functions

void load_string_to_memory(const char *string, uint32_t address) {
    strcpy((char *)memory + address, string);
}

void load_instruction(uint32_t address, uint32_t instruction) {
    memcpy(&memory[address], &instruction, sizeof(instruction));
}

void load_instructions_from_txt(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    char line[256];
    uint32_t address = PC_START;
    while (fgets(line, sizeof(line), file)) {
        uint32_t instruction;
        if (sscanf(line, "%x", &instruction) == 1) {
            load_instruction(address, instruction);
            address += 4;
        }
    }

    fclose(file);
}