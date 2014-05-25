# c flag
CFLAG=-std=c99 -Wall
# delete files
RM=rm -rf
# create directory
MKDIR=-mkdir -p
# binary file directory
BIN_DIR=../bin/chapter-14

# make build
build:
	$(MKDIR) $(BIN_DIR)
	@echo Compiling chapter 14 codes...
	$(CC) $(CFLAG) write.c -o $(BIN_DIR)/write
	$(CC) $(CFLAG) deadlock.c -o $(BIN_DIR)/deadlock
	$(CC) $(CFLAG) mandatory.c -o $(BIN_DIR)/mandatory

.PHONY: clean

clean:
	$(RM) $(BIN_DIR)
