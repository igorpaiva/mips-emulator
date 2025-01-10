CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude -I$(TEST_DIR)/rktest
SRC_DIR = src
BUILD_DIR = $(SRC_DIR)/build
TEST_DIR = test
TEST_BUILD_DIR = $(TEST_DIR)/build

EXEC = $(BUILD_DIR)/mips_emulator
TEST_EXEC = $(TEST_BUILD_DIR)/mips_tests

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))

TEST_SRC = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJ = $(patsubst $(TEST_DIR)/%.c,$(TEST_BUILD_DIR)/%.o,$(TEST_SRC))

RKTEST_OBJ = $(TEST_BUILD_DIR)/rktest.o

.PHONY: all clean run test

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(TEST_EXEC): $(filter-out $(BUILD_DIR)/main.o, $(OBJ)) $(TEST_OBJ) $(RKTEST_OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -lm

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_BUILD_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(TEST_BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(RKTEST_OBJ): $(TEST_DIR)/rktest/rktest.c
	@mkdir -p $(TEST_BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

run: $(EXEC)
	./$(EXEC)

test: $(TEST_EXEC)
	./$(TEST_EXEC)

clean:
	rm -rf $(BUILD_DIR) $(TEST_BUILD_DIR)
