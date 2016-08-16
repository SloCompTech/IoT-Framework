
# Variables
DIR_ROOT = ${PWD}
DIR_LIB_C = ./lib/C
DIR_LIB_LUA = ./lib/lua
DIR_LIB_PYTHON = ./lib/python
DIR_MOD = ./modules
DIR_CONF = ./conf
DIR_BIN = ./bin
DIR_SRC = ./src
DIR_SAMPLES = ./samples

# Export section
export DIR_LIB_C
export DIR_LIB_LUA
export DIR_LIB_PYTHON
export DIR_MOD
export DIR_CONF
export DIR_BIN
export DIR_SRC
export DIR_SAMPLES
export DIR_ROOT

all:
	@echo "You entered wrong option"

#Intall section
install:
	@echo "Not finished yet"


# Compile section
compile: compile-lib compile-core
	@echo "Not defined yet"

compile-lib:
	$(MAKE) -C $(DIR_LIB_C)

compile-core:
	$(MAKE) -C $(DIR_SRC)/CoreServer OUTPUT=../../$(DIR_BIN)/Core

# Run section
run-core:
	$(DIR_BIN)/Core
