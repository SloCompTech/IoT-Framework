# Variables from main make:
# 	DIR_LIB_C

DIR_LIB_C = ../../lib/C


LIB_CPP = $(DIR_LIB_C)/jsoncpp/dist/jsoncpp.o
BINARY_FILES = $(wildcard $(DIR_LIB_C)/*.o) $(wildcard $(DIR_LIB_C)/*/*.o)



build:
	echo $(OUTPUT)
	g++ *.cpp $(BINARY_FILES) $(LIB_CPP) -I $(DIR_LIB_C) -std=c++11 -o $(OUTPUT) -pthread
