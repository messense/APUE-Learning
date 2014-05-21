# c flag
CFLAG=-std=c99 -Wall
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
	$(CC) $(CFLAG) atexit.c -o $(BIN_DIR)/atexit
	$(CC) $(CFLAG) printargs.c -o $(BIN_DIR)/printargs
	$(CC) $(CFLAG) setjmp.c -o $(BIN_DIR)/setjmp
	$(CC) $(CFLAG) longjmp.c -o $(BIN_DIR)/longjmp
	$(CC) $(CFLAG) -O longjmp.c -o $(BIN_DIR)/longjmp_o
	$(CC) $(CFLAG) printrlimit.c -o $(BIN_DIR)/printrlimit

.PHONY: clean

clean:
	$(RM) $(BIN_DIR)
