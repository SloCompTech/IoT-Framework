LIB_DIR = ../lib
INCLUDE_DIR = ../lib
MAIN_CPP=Core.cpp
OUTPUT_FILE=Core


build:
	g++ $(MAIN_CPP)  $(LIB_DIR)/Log/*.o $(LIB_DIR)/ProcessManip/*.o $(LIB_DIR)/TCPServer/*.o $(LIB_DIR)/Convert/*.o -I $(INCLUDE_DIR) -std=c++11 -o $(OUTPUT_FILE)
