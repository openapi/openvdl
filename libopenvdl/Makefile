CC ?= cc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -Iinclude

BUILD_DIR := build
LIB := $(BUILD_DIR)/libopenvdl.a
TEST_BIN := $(BUILD_DIR)/test_openvdl

SRC := src/openvdl.c
OBJ := $(SRC:src/%.c=$(BUILD_DIR)/%.o)

.PHONY: all clean test

all: $(LIB)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: src/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB): $(OBJ)
	ar rcs $@ $^

$(TEST_BIN): tests/test_openvdl.c $(LIB)
	$(CC) $(CFLAGS) tests/test_openvdl.c $(LIB) -o $@

test: $(TEST_BIN)
	$(TEST_BIN)

clean:
	rm -rf $(BUILD_DIR)
