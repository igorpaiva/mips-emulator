#include "rktest/rktest.h"
#include "memory.h"
#include "syscall.h"
#include "instructions.h"

TEST_SETUP(syscall_tests){
    reset_registers_and_memory();
}

TEST(syscall_tests, test_print_string) {
    addi(v0, zero, 4);
    addi(a0, zero, 8);

    char *string = "Hello, World!";
    store_string_in_memory(string, registers[a0]);

    syscall();
    // TODO: Test if the string was logged
}

TEST(syscall_tests, test_exit) {
    addi(v0, zero, 10);
    // syscall(); // TODO: Implement exit syscall mock
}

TEST(syscall_tests, test_unknown_syscall) {
    addi(v0, zero, 0x20);
    syscall();
}