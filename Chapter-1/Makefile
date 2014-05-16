# compiler
CC=cc
# delete files
RM=rm -rf
# create directory
MKDIR=-mkdir -p
# binary file directory
BIN_DIR=../bin/chapter-1

.PHONY: build

# make build
build:
	$(MKDIR) $(BIN_DIR)
	@echo Starting compile chapter 1 codes...
	$(CC) ls.c -o $(BIN_DIR)/ls
	$(CC) in2out1.c -o $(BIN_DIR)/in2out1
	$(CC) in2out2.c -o $(BIN_DIR)/in2out2
	$(CC) printpid.c -o $(BIN_DIR)/printpid
	$(CC) cmd1.c -o $(BIN_DIR)/cmd1
	$(CC) cmd2.c -o $(BIN_DIR)/cmd2
	$(CC) printerror.c -o $(BIN_DIR)/printerror
	$(CC) printuser.c -o $(BIN_DIR)/printuser

.PHONY: clean

clean:
	$(RM) $(BIN_DIR)
