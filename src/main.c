#include <string.h>
#include "memory.h"
#include "instructions.h"

#define MEMORY_DEBUG_SECTION 10

int main() {

    uint32_t instruction;
    
    reset_pc();

    log_set_level(LOG_DEBUG);
    // log_set_level(LOG_INFO);

    // Reset registers and memory
    reset_registers_and_memory();

    // Load "Hello, World!" string into memory
    const char *hello_world = "Hello, World!\n";
    strcpy((char *)memory+8, hello_world);

    // Log string stored in memory
    log_debug((char *)memory+8);

    // Load instructions from file
    load_instructions_from_txt("program.txt");

    if (log_get_level() == LOG_DEBUG) {
        char log_buffer[LOG_DEFAULT_BUFFER_SIZE];
        int offset = 0;

        offset += snprintf(log_buffer, sizeof(log_buffer), "\nData memory: \n");

        for (int i = 0; i < MEMORY_DEBUG_SECTION * 4; i += 4) {
            offset += snprintf(log_buffer + offset, sizeof(log_buffer) - offset, "%02X: 0x%08X\n", i, *(uint32_t *)&memory[i]);
        }

        log_debug("%s", log_buffer);
    }

    if (log_get_level() == LOG_DEBUG) {
        char log_buffer[LOG_DEFAULT_BUFFER_SIZE];
        int offset = 0;

        offset += snprintf(log_buffer, sizeof(log_buffer), "\nText memory: \n");

        for (int i = pc; i < (int)pc + MEMORY_DEBUG_SECTION * 4; i += 4) {
            offset += snprintf(log_buffer + offset, sizeof(log_buffer) - offset, "%02X: 0x%08X\n", i, *(uint32_t *)&memory[i]);
        }

        log_debug("%s", log_buffer);
    }

    log_debug("Starting execution...\n");

    while (pc < MEMORY_SIZE) {
        instruction = *(uint32_t*)&memory[pc];
        decode_instruction(instruction);
        pc += 4;
    }

    return 0;
}