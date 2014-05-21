# c flag
CFLAG=-std=c99 -Wall
# delete files
RM=rm -rf
# create directory
MKDIR=-mkdir -p
# binary file directory
BIN_DIR=../bin/chapter-2

.PHONY: build

# make build
build:
	$(MKDIR) $(BIN_DIR)
	@echo Compiling chapter 2 codes...
	$(CC) $(CFLAG) -Wno-unused-function printconf.c -o $(BIN_DIR)/printconf
	$(CC) $(CFLAG) pathmax.c -o $(BIN_DIR)/pathmax
	$(CC) $(CFLAG) openmax.c -o $(BIN_DIR)/openmax

.PHONY: clean

clean:
	$(RM) $(BIN_DIR)
