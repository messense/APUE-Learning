# compiler
CC=cc -std=c99 -Wall
# delete files
RM=rm -rf
# create directory
MKDIR=-mkdir -p
# binary file directory
BIN_DIR=../bin/chapter-8
# platform
OS := $(shell uname)
ifeq ($(OS), Darwin)
	WNODIV=-Wno-division-by-zero
else
	WNODIV=-Wno-div-by-zero
endif

# make build
build:
	$(MKDIR) $(BIN_DIR)
	@echo Compiling chapter 8 codes...
	$(CC) processinfo.c -o $(BIN_DIR)/processinfo
	$(CC) fork.c -o $(BIN_DIR)/fork
	$(CC) vfork.c -o $(BIN_DIR)/vfork
	$(CC) $(WNODIV) printexit.c -o $(BIN_DIR)/printexit
	$(CC) forktwice.c -o $(BIN_DIR)/forktwice
	$(CC) charatatime1.c -o $(BIN_DIR)/charatatime1
	$(CC) charatatime2.c -o $(BIN_DIR)/charatatime2
	$(CC) charatatime3.c -o $(BIN_DIR)/charatatime3
	$(CC) exec.c -o $(BIN_DIR)/exec
	$(CC) system.c -o $(BIN_DIR)/system
	$(CC) genacct.c -o $(BIN_DIR)/genacct
	$(CC) pracct.c -o $(BIN_DIR)/pracct
	$(CC) printlogin.c -o $(BIN_DIR)/printlogin
	$(CC) nice.c -o $(BIN_DIR)/nice
	$(CC) printtimes.c -o $(BIN_DIR)/printtimes

.PHONY: clean

clean:
	$(RM) $(BIN_DIR)
