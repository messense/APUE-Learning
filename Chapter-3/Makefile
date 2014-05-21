# c flag
CFLAG=-std=c99 -Wall
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
	@echo Compiling chapter 3 codes...
	$(CC) $(CFLAG) stdin_seek.c -o $(BIN_DIR)/stdin_seek
	$(CC) $(CFLAG) filehole.c -o $(BIN_DIR)/filehole
	$(CC) $(CFLAG) printflags.c -o $(BIN_DIR)/printflags

.PHONY: clean

clean:
	$(RM) $(BIN_DIR)
