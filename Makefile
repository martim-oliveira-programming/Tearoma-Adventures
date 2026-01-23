CC ?= cc
CPPFLAGS ?= -Iinclude
CFLAGS ?= -Wall -Wextra -Wpedantic -std=c11 -g -Wno-newline-eof

SRC_DIR := src
BUILD_DIR := build
TARGET := tearoma

SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))
DEP := $(OBJ:.o=.d)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $(OBJ)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

-include $(DEP)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJ) $(DEP) $(TARGET)
	rmdir $(BUILD_DIR) 2>/dev/null || true
