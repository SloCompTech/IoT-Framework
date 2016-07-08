LIB_DIR = ../../lib
INCLUDE_DIR = ../../lib
MAIN_CPP=Client.cpp
OUTPUT_FILE=Client


build:
	g++ $(MAIN_CPP)  $(LIB_DIR)/Log/*.o   $(LIB_DIR)/Convert/*.o $(LIB_DIR)/TCPClient/*.o $(LIB_DIR)/SocketManip/*.o -I $(INCLUDE_DIR) -std=c++11 -o $(OUTPUT_FILE)
