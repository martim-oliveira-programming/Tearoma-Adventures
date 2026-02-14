CC ?= cc
CPPFLAGS ?= -Iinclude
CFLAGS ?= -Wall -Wextra -Wpedantic -std=c11 -g -Wno-newline-eof
LDFLAGS ?=

UNAME_S := $(shell uname -s)

# Raylib flags (override if your install differs)
ifeq ($(UNAME_S),Linux)
RAYLIB_LIBS ?= -lraylib -lm -lpthread -ldl -lrt -lGL
RAYLIB_LDFLAGS ?=
RAYLIB_CFLAGS ?=
else
# macOS default (Homebrew raylib in /opt/homebrew)
RAYLIB_LIBS ?= -lraylib -framework Cocoa -framework IOKit -framework CoreVideo -framework OpenGL
RAYLIB_LDFLAGS ?= -L/opt/homebrew/lib
RAYLIB_CFLAGS ?= -I/opt/homebrew/include
endif

SRC_DIR := src
BUILD_DIR := build
TARGET := tearoma

SRC := $(shell find $(SRC_DIR) -name '*.c')
OBJ := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))
DEP := $(OBJ:.o=.d)

.PHONY: all run clean game

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(RAYLIB_CFLAGS) $(LDFLAGS) $(RAYLIB_LDFLAGS) -o $@ $(OBJ) $(RAYLIB_LIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(RAYLIB_CFLAGS) -MMD -MP -c $< -o $@

-include $(DEP)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJ) $(DEP) $(TARGET)
	rm -rf $(BUILD_DIR)

# Standalone build of main.c only (macOS 26.3 ARM, Homebrew raylib)
game:
	gcc src/main.c -o game \
		-L/opt/homebrew/lib \
		-I/opt/homebrew/include \
		-lraylib \
		-framework OpenGL \
		-framework Cocoa \
		-framework IOKit \
		-framework CoreVideo
