#ifndef SYSCALL_H
#define SYSCALL_H

#include "memory.h"

void syscall();
void syscall_handler(uint32_t syscall_code);

#endif