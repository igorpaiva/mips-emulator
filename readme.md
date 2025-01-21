[![CI](https://github.com/igorpaiva/mips-emulator/actions/workflows/ci.yml/badge.svg)](https://github.com/igorpaiva/mips-emulator/actions/workflows/ci.yml)
# MIPS emulator

This project is a WIP 32-bit MIPS emulator written in C. It includes functionality to load and execute MIPS instructions, as well as unit tests to verify the correctness of the implementation.

The project uses the external libraries [RKtest](https://github.com/Warwolt/rktest) and [log.c](https://github.com/rxi/log.c) that are built along with the emulator. These external libs are not shown in the project structure below.

## Project Structure

```
mips_emulator/ 
│    ├── include/ 
│    │    ├── syscall.h 
│    │    ├── memory.h 
│    │    └── instructions.h 
│    ├── src/
│    │    ├── main.c
│    │    ├── syscall.c
│    │    ├── memory.c 
│    │    └── instructions.c 
│    ├── test/ 
│    │    ├── test_decode.c
│    │    ├── test_memory.c
│    │    ├── test_instructions.c
│    │    └── test.template
│    ├── Makefile 
└    └── README.md
```

## Prerequisites

- GCC (GNU Compiler Collection)
- `make`
- `lcov` (for code coverage)

## Setup

1. **Clone the repository:**

   ```sh
   git clone https://github.com/yourusername/mips_emulator.git
   cd mips_emulator
   ```

2. **Install dependencies:**

    On Ubuntu, you can install the required packages using

    ```sh
    sudo apt-get install build-essential lcov
    ```
## Building the project

To build the project, run:

```sh
make    
```
This will compile the source files and create the executable `mips_emulator` in the `build` directory.

## Running the emulator

To run the emulator, use:

```sh
make run    
```

This will execute the `mips_emulator` binary.

## Running the tests

To build and run the tests, use:

```sh
make test
```

This will compile the test files and run the test executable `test_runner`.

## Generating Code Coverage Report

To generate a code coverage report, use:

```sh
make coverage
```

This will run the tests, capture the coverage data using `lcov`, and generate an HTML report in the `out` directory.

### Current code coverage

The current code coverage is shown below:

![image](https://github.com/user-attachments/assets/cf4e7b61-9d47-4c34-9619-c79b1ca67aa2)

## Cleaning the build folders and coverage files

To clean the folders created with the previous commands, use:

```sh
make clean
```
## Project Details

### Memory
The memory module includes functions to reset and manage the memory used by the emulator.

### Instructions
The instructions module includes implementations of various MIPS instructions such as `add`, `addi`, `slti`, `sltiu`, etc.

### Load Program
The load program module includes functions to load instructions from a file into memory.

### Logging
The project includes a logging mechanism to log debug information. The log level can be set to `LOG_DEBUG` to enable detailed logging.

### Example Usage
Loading Instructions
Instructions can be loaded from a file named program.txt. The file should contain MIPS instructions in hexadecimal format.

### Debugging
When the log level is set to `LOG_DEBUG`, the emulator logs detailed information about the memory and instructions being executed.

### Contributing
Contributions are welcome! Please fork the repository and submit pull requests.
