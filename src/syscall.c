#include "syscall.h"

#define DEFAULT_SYSCALL_REGISTER 2
#define DEFAULT_STRING_REGISTER 4

void syscall() {
    syscall_handler(registers[DEFAULT_SYSCALL_REGISTER]);
}

void syscall_handler(uint32_t syscall_code) {
    switch (syscall_code) {
        case 4:  // Log string (syscall 4)
            log_info("%s", (char *)memory+registers[DEFAULT_STRING_REGISTER]);
            break;
        case 10:  // Exit (syscall 10)
            log_debug("Exiting program...\n");
            exit(0);
            break;
        default:
            log_error("Unknown or not implemented syscall %d\n", syscall_code);
            break;
    }
}