# compiler
CC=cc -std=c99 -Wall
# delete files
RM=rm -rf
# create directory
MKDIR=-mkdir -p
# binary file directory
BIN_DIR=../bin/chapter-5

.PHONY: build

# make build
build:
	$(MKDIR) $(BIN_DIR)
	@echo Compiling chapter 5 codes...
	$(CC) in2out1.c -o $(BIN_DIR)/in2out1
	$(CC) in2out2.c -o $(BIN_DIR)/in2out2
	$(CC) buf.c -o $(BIN_DIR)/buf
	$(CC) tempfiles.c -o $(BIN_DIR)/tempfiles
	$(CC) mkstemp.c -o $(BIN_DIR)/mkstemp
	$(CC) memstr.c -o $(BIN_DIR)/memstr

.PHONY: clean

clean:
	$(RM) $(BIN_DIR)
