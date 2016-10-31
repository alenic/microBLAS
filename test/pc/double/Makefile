# Test-double Makefile for microBLAS

#General
MBLAS_ROOT_PATH=../../..

include $(MBLAS_ROOT_PATH)/make.inc

CC=g++
CFLAGS=-O3 -fPIC -D__cpp

LOCAL_INCLUDE_FILES = $(MBLAS_ROOT_PATH)/include/dmicroBLAS.h
EXECUTABLE=double_test.out
LIBFLAGS=-ldmicroBLAS

# Includes
LOCAL_INCLUDE_PATH = $(MBLAS_ROOT_PATH)/include ../ $(MBLAS_ROOT_PATH)/$(GTEST_H)
L_HEADERS = $(addprefix -I,$(LOCAL_INCLUDE_PATH))

#lib
LOCAL_LIB_PATH=$(MBLAS_ROOT_PATH)/lib/pc
L_LIB=-L$(LOCAL_LIB_PATH)
LOCAL_OBJECT_FILES=$(addprefix $(LOCAL_OBJ_PATH)/,$(OBJECTS))

default: all

all: ./$(EXECUTABLE)

./$(EXECUTABLE): ./*.c $(LOCAL_INCLUDE_FILES)
	$(CC) $(CFLAGS) $(L_HEADERS) -o ./$(EXECUTABLE) ./*.c $(L_LIB) $(LIBFLAGS) $(MBLAS_ROOT_PATH)/$(GTEST_LIB) -lpthread
	@echo "****************** $(EXECUTABLE) Done ******************"

# Clean all
clean:
	rm ./$(EXECUTABLE)

.PHONY: clean