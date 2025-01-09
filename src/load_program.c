#include "load_program.h"

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
    uint32_t address = 0;
    while (fgets(line, sizeof(line), file)) {
        uint32_t instruction;
        if (sscanf(line, "%x", &instruction) == 1) {
            load_instruction(address, instruction);
            address += 4;
        }
    }

    fclose(file);
}