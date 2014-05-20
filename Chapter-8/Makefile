# compiler
CC=cc -std=c99 -Wall
# delete files
RM=rm -rf
# create directory
MKDIR=-mkdir -p
# binary file directory
BIN_DIR=../bin/chapter-8

.PHONY: build

# make build
build:
	$(MKDIR) $(BIN_DIR)
	@echo Compiling chapter 8 codes...
	$(CC) processinfo.c -o $(BIN_DIR)/processinfo
	$(CC) fork.c -o $(BIN_DIR)/fork
	$(CC) vfork.c -o $(BIN_DIR)/vfork
	$(CC) -Wno-division-by-zero printexit.c -o $(BIN_DIR)/printexit

.PHONY: clean

clean:
	$(RM) $(BIN_DIR)
