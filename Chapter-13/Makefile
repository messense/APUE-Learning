# c flag
CFLAG=-std=c99 -Wall
# delete files
RM=rm -rf
# create directory
MKDIR=-mkdir -p
# binary file directory
BIN_DIR=../bin/chapter-13

# make build
build:
	$(MKDIR) $(BIN_DIR)
	@echo Compiling chapter 13 codes...
	$(CC) $(CFLAG) daemonize.c -o $(BIN_DIR)/daemonize
	$(CC) $(CFLAG) single.c -o $(BIN_DIR)/single
	$(CC) $(CFLAG) -pthread reread1.c -o $(BIN_DIR)/reread1
	$(CC) $(CFLAG) -pthread reread2.c -o $(BIN_DIR)/reread2

.PHONY: clean

clean:
	$(RM) $(BIN_DIR)
