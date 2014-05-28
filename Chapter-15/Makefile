# c flag
CFLAG=-std=c99 -Wall
# delete files
RM=rm -rf
# create directory
MKDIR=-mkdir -p
# binary file directory
BIN_DIR=../bin/chapter-15

# make build
build:
	$(MKDIR) $(BIN_DIR)
	@echo Compiling chapter 15 codes...
	$(CC) $(CFLAG) pipe.c -o $(BIN_DIR)/pipe


.PHONY: clean

clean:
	$(RM) $(BIN_DIR)
