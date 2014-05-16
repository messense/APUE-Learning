# compiler
CC=cc -std=c99 -Wall
# delete files
RM=rm -rf
# create directory
MKDIR=-mkdir -p
# binary file directory
BIN_DIR=../bin/chapter-3

.PHONY: build

# make build
build:
	$(MKDIR) $(BIN_DIR)
	@echo Starting compile chapter 3 codes...
	$(CC) stdin_seek.c -o $(BIN_DIR)/stdin_seek
	$(CC) filehole.c -o $(BIN_DIR)/filehole
	$(CC) printflags.c -o $(BIN_DIR)/printflags

.PHONY: clean

clean:
	$(RM) $(BIN_DIR)
