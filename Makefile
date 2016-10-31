# Main Makefile for microBLAS

default: all

all: pc test_pc

pc: pc_double

pc_double: src_pc_double

src_pc_double:
	(cd src/pc; make make_double)

test_pc: test_pc_double

test_pc_double:
	(cd ./test; make all)

clean: clean_src_double clean_test_double



clean_src_double:
	(cd src; make clean)

clean_test_double:
	(cd ./test; make clean)

