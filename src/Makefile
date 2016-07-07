LIB_DIR = ../lib
INCLUDE_DIR = ../lib
MAIN_CPP=Core.cpp
OUTPUT_FILE=Core

BINARY_FILES = $(wildcard ../lib/*.o) $(wildcard ../lib/*/*.o)

build:
	g++ $(MAIN_CPP)  $(BINARY_FILES) -I $(INCLUDE_DIR) -std=c++11 -o $(OUTPUT_FILE)
