# Compiler
CC=gcc
CPP=g++
CFLAGS=-O3
CPPFLAGS=-O3

# Test
EXECUTABLE=mainTest.out

LOCAL_TEST_PATH=./test

default: all

all: test

test: $(LOCAL_TEST_PATH)/$(EXECUTABLE)

test/$(EXECUTABLE): $(LOCAL_TEST_PATH)/*.c microBLAS/microBLAS.h microBLAS/microBLAS.c
	$(CPP) $(CPPFLAGS) -o $(EXECUTABLE) $(LOCAL_TEST_PATH)/*.c microBLAS/microBLAS.c -ImicroBLAS/ -I$(LOCAL_TEST_PATH) -lgtest -lpthread
	@echo "****************** Test: $(EXECUTABLE) [OK] ******************"

# Clean
clean:
	(test $(EXECUTABLE) && rm $(EXECUTABLE) || true)
	@echo "****************** Clean [OK] ******************"

.PHONY: clean
