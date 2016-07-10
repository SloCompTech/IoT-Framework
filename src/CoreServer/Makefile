LIB_DIR = ../../lib
INCLUDE_DIR = ../../lib
MAIN_CPP=Core.cpp
FILE_CPP=ConnectionHandler.cpp
OUTPUT_FILE=Core
LIB_CPP = $(LIB_DIR)/jsoncpp/dist/jsoncpp.o
BINARY_FILES = $(wildcard ../../lib/*.o) $(wildcard ../../lib/*/*.o)

build:
	g++ $(MAIN_CPP)  $(FILE_CPP) $(BINARY_FILES) $(LIB_CPP) -I $(INCLUDE_DIR) -std=c++11 -o $(OUTPUT_FILE) -pthread
