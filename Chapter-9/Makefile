# c flag
CFLAG=-std=c99 -Wall
# delete files
RM=rm -rf
# create directory
MKDIR=-mkdir -p
# binary file directory
BIN_DIR=../bin/chapter-9

.PHONY: build

# make build
build:
	$(MKDIR) $(BIN_DIR)
	@echo Compiling chapter 9 codes...
	$(CC) $(CFLAG) orphan.c -o $(BIN_DIR)/orphan

.PHONY: clean

clean:
	$(RM) $(BIN_DIR)
