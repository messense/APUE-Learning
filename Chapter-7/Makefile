# compiler
CC=cc -std=c99 -Wall
# delete files
RM=rm -rf
# create directory
MKDIR=-mkdir -p
# binary file directory
BIN_DIR=../bin/chapter-7

.PHONY: build

# make build
build:
	$(MKDIR) $(BIN_DIR)
	@echo Compiling chapter 7 codes...
	$(CC) atexit.c -o $(BIN_DIR)/atexit
	$(CC) printargs.c -o $(BIN_DIR)/printargs
	$(CC) setjmp.c -o $(BIN_DIR)/setjmp
	$(CC) longjmp.c -o $(BIN_DIR)/longjmp
	$(CC) -O longjmp.c -o $(BIN_DIR)/longjmp_o
	$(CC) printrlimit.c -o $(BIN_DIR)/printrlimit

.PHONY: clean

clean:
	$(RM) $(BIN_DIR)
