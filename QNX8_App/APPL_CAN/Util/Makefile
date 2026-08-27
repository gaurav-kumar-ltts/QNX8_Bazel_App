# QNX SDP 8.0 Makefile for MCP2515 Test Utility
# Target Architecture: AArch64 (Raspberry Pi 5)

NAME = mcp2515
CC = qcc
TARGET_ARCH = -Vgcc_ntoaarch64le

# Compiler & Linker Flags
CFLAGS = -Wall -Wextra -O2
LDFLAGS = 

# Directories
BUILD_DIR = build/aarch64le
SRC = mcp2515.c
OBJ = $(BUILD_DIR)/mcp2515.o
TARGET = $(BUILD_DIR)/$(NAME)

.PHONY: all clean

all: $(TARGET)

# Ensure build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compile C source files to object files
$(OBJ): $(SRC) | $(BUILD_DIR)
	$(CC) $(TARGET_ARCH) $(CFLAGS) -c $< -o $@

# Link object files into final executable
$(TARGET): $(OBJ)
	$(CC) $(TARGET_ARCH) $(LDFLAGS) $< -o $@
	@echo "Build complete: $(TARGET)"

clean:
	rm -rf build