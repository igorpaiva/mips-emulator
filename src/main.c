#include <string.h>
#include "load_program.h"
#include "memory.h"

int main() {
    // Reset registers and memory
    reset_registers_and_memory();

    // Load instructions from file
    load_instructions_from_txt("program.txt");

    // Print every word stored in memory for debugging
    int mem_debug_section = 10;
    for (int i = 0; i < mem_debug_section * 4; i += 4) {
        printf("0x%08X\n", *(uint32_t *)&memory[i]);
    }

    return 0;
}