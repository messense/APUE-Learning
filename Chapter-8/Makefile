# compiler
CC=cc -std=c99 -Wall
# delete files
RM=rm -rf
# create directory
MKDIR=-mkdir -p
# binary file directory
BIN_DIR=../bin/chapter-8
# platform
OS := $(shell uname)
ifeq ($(OS), Darwin)
	NODIV=-Wno-division-by-zero
else
	NODIV=-Wno-div-by-zero
endif

# make build
build:
	$(MKDIR) $(BIN_DIR)
	@echo Compiling chapter 8 codes...
	$(CC) processinfo.c -o $(BIN_DIR)/processinfo
	$(CC) fork.c -o $(BIN_DIR)/fork
	$(CC) vfork.c -o $(BIN_DIR)/vfork
	$(CC) $(NODIV) printexit.c -o $(BIN_DIR)/printexit

.PHONY: clean

clean:
	$(RM) $(BIN_DIR)
