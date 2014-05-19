# compiler
CC=cc -std=c99 -Wall
# delete files
RM=rm -rf
# create directory
MKDIR=-mkdir -p
# binary file directory
BIN_DIR=../bin/chapter-6

.PHONY: build

# make build
build:
	$(MKDIR) $(BIN_DIR)
	@echo Compiling chapter 6 codes...
	$(CC) getpwnam.c -o $(BIN_DIR)/getpwnam
	$(CC) formattime.c -o $(BIN_DIR)/formattime
	$(CC) uname.c -o $(BIN_DIR)/uname
	$(CC) date.c -o $(BIN_DIR)/date

.PHONY: clean

clean:
	$(RM) $(BIN_DIR)
