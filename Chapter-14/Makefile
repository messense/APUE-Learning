# c flag
CFLAG=-std=c99 -Wall
# delete files
RM=rm -rf
# create directory
MKDIR=-mkdir -p
# binary file directory
BIN_DIR=../bin/chapter-14
# platform
OS := $(shell uname)
ifeq ($(OS), Darwin)
	LDFLAG=
else
	LDFLAG=-lrt
endif

# make build
build:
	$(MKDIR) $(BIN_DIR)
	@echo Compiling chapter 14 codes...
	$(CC) $(CFLAG) write.c -o $(BIN_DIR)/write
	$(CC) $(CFLAG) deadlock.c -o $(BIN_DIR)/deadlock
	$(CC) $(CFLAG) mandatory.c -o $(BIN_DIR)/mandatory
	$(CC) $(CFLAG) rot13a.c -o $(BIN_DIR)/rot13a
	$(CC) $(CFLAG) rot13c.c -o $(BIN_DIR)/rot13c $(LDFLAG)


.PHONY: clean

clean:
	$(RM) $(BIN_DIR)
