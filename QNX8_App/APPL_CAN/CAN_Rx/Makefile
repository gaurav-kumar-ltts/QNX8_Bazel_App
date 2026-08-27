# QNX SDP 8.0 Makefile for the 10 ms MCP2515 CAN receiver

NAME = appl_can_rx
CC = qcc
TARGET_ARCH = -Vgcc_ntoaarch64le
CFLAGS = -Wall -Wextra -O2

BUILD_DIR = build/aarch64le
SRC = appl_can_rx.c
OBJ = $(BUILD_DIR)/appl_can_rx.o
TARGET = $(BUILD_DIR)/$(NAME)

.PHONY: all clean

all: $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(OBJ): $(SRC) | $(BUILD_DIR)
	$(CC) $(TARGET_ARCH) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(TARGET_ARCH) $< -o $@
	@echo "Build complete: $(TARGET)"

clean:
	rm -rf build