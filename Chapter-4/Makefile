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
	$(CC) unlink.c -o $(BIN_DIR)/unlink
	$(CC) futimens.c -o $(BIN_DIR)/futimens
	$(CC) ftw.c -o $(BIN_DIR)/ftw
	$(CC) chdir.c -o $(BIN_DIR)/chdir
	$(CC) getcwd.c -o $(BIN_DIR)/getcwd
	$(CC) printdev.c -o $(BIN_DIR)/printdev

.PHONY: clean

clean:
	$(RM) $(BIN_DIR)
