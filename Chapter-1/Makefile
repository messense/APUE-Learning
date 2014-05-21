# c flag
CFLAG=-std=c99 -Wall
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
	@echo Compiling chapter 1 codes...
	$(CC) $(CFLAG) ls.c -o $(BIN_DIR)/ls
	$(CC) $(CFLAG) in2out1.c -o $(BIN_DIR)/in2out1
	$(CC) $(CFLAG) in2out2.c -o $(BIN_DIR)/in2out2
	$(CC) $(CFLAG) printpid.c -o $(BIN_DIR)/printpid
	$(CC) $(CFLAG) cmd1.c -o $(BIN_DIR)/cmd1
	$(CC) $(CFLAG) cmd2.c -o $(BIN_DIR)/cmd2
	$(CC) $(CFLAG) printerror.c -o $(BIN_DIR)/printerror
	$(CC) $(CFLAG) printuser.c -o $(BIN_DIR)/printuser

.PHONY: clean

clean:
	$(RM) $(BIN_DIR)
