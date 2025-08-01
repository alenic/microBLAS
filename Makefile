# Compiler and flags
CC      := gcc
CFLAGS  := -O2 -Wall -Wextra -std=c11
LDFLAGS := -lm

# Targets
TARGET  := test_microBLAS
SRC     := test_microBLAS.c

# Default target
all: $(TARGET)

$(TARGET): $(SRC) microBLAS.h
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

# Run tests
run: $(TARGET)
	./$(TARGET)

# Clean build files
clean:
	rm -f $(TARGET)

.PHONY: all run clean