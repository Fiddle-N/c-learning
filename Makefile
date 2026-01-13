# Compiler and flags
CC := gcc
CFLAGS := -Wall -Wextra -Wpedantic -Werror -fsanitize=address,undefined -std=c23 -Ilib/utils
LDFLAGS := -fsanitize=address,undefined

# Directories
BUILD := build

# Explicit tools
TOOLS := hello_world hello_world_2 read_file
BINS := $(TOOLS:%=$(BUILD)/%)

# Default target
.PHONY: all
all: $(BINS)

# ---- Build executables ----
$(BUILD)/%: $(BUILD)/%.o $(BUILD)/utils.o
	$(CC) $^ -o $@ $(LDFLAGS)

# ---- Compile tool main.c into object ----
$(BUILD)/%.o: tools/%/main.c | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

# ---- Compile library utils.c into object ----
$(BUILD)/utils.o: lib/utils/utils.c | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

# ---- Ensure build directory exists ----
$(BUILD):
	mkdir -p $(BUILD)

# ---- Clean build artifacts ----
.PHONY: clean
clean:
	rm -rf $(BUILD)
