# QNX 8.0 Makefile for CAN Application (Raspberry Pi 5 / aarch64le)

CC = qcc
TARGET = gcc_ntoaarch64le
CFLAGS = -V$(TARGET) -O2 -Wall -Wextra
LDFLAGS = 

SRCS = appl_can_rx.c
OBJS = $(SRCS:.c=.o)
EXEC = can_app

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)

.PHONY: all clean