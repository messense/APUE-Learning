# compiler
CC=cc -std=c99 -Wall
# delete files
RM=rm -rf
# create directory
MKDIR=-mkdir -p
# binary file directory
BIN_DIR=../bin/chapter-4

.PHONY: build

# make build
build:
	$(MKDIR) $(BIN_DIR)
	@echo Starting compile chapter 4 codes...
	$(CC) printstat.c -o $(BIN_DIR)/printstat
	$(CC) access.c -o $(BIN_DIR)/access
	$(CC) umask.c -o $(BIN_DIR)/umask
	$(CC) chmod.c -o $(BIN_DIR)/chmod

.PHONY: clean

clean:
	$(RM) $(BIN_DIR)
