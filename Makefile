# Compiler and flags
CC      := gcc
CFLAGS  := -O2 -Wall -Wextra -std=c11
LDFLAGS := -lm

# Targets
TEST_TARGET  := tests.out
TEST_SRC     := tests.c

# Benchmarks
BENCHMARKS_TARGET := benchmarks.out
BENCHMARKS_SRC := benchmarks.c

# Default target
all: $(TEST_TARGET) $(BENCHMARKS_TARGET)

$(TEST_TARGET): $(TEST_SRC) microBLAS.h
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(TEST_SRC) $(LDFLAGS)

# Run tests
run: $(TEST_TARGET)
	./$(TEST_TARGET)

$(BENCHMARKS_TARGET): $(BENCHMARKS_SRC) microBLAS.h
	$(CC) $(CFLAGS) -o $(BENCHMARKS_TARGET) $(BENCHMARKS_SRC) $(LDFLAGS)


benchmarks: $(BENCHMARKS_TARGET)
			./$(BENCHMARKS_TARGET)

# Clean build files
clean:
	rm -f $(TARGET)

.PHONY: all run clean