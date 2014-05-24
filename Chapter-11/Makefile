# c flag
CFLAG=-std=c99 -Wall -pthread
# delete files
RM=rm -rf
# create directory
MKDIR=-mkdir -p
# binary file directory
BIN_DIR=../bin/chapter-11

.PHONY: build

# make build
build:
	$(MKDIR) $(BIN_DIR)
	@echo Compiling chapter 11 codes...
	$(CC) $(CFLAG) threadid.c -o $(BIN_DIR)/threadid
	$(CC) $(CFLAG) pthreadexit1.c -o $(BIN_DIR)/pthreadexit1
	$(CC) $(CFLAG) pthreadexit2.c -o $(BIN_DIR)/pthreadexit2
	$(CC) $(CFLAG) cleanup.c -o $(BIN_DIR)/cleanup

.PHONY: clean

clean:
	$(RM) $(BIN_DIR)
