# c flag
CFLAG=-std=c99 -Wall
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
	$(CC) $(CFLAG) processinfo.c -o $(BIN_DIR)/processinfo
	$(CC) $(CFLAG) fork.c -o $(BIN_DIR)/fork
	$(CC) $(CFLAG) vfork.c -o $(BIN_DIR)/vfork
	$(CC) $(CFLAG) $(WNODIV) printexit.c -o $(BIN_DIR)/printexit
	$(CC) $(CFLAG) forktwice.c -o $(BIN_DIR)/forktwice
	$(CC) $(CFLAG) charatatime1.c -o $(BIN_DIR)/charatatime1
	$(CC) $(CFLAG) charatatime2.c -o $(BIN_DIR)/charatatime2
	$(CC) $(CFLAG) charatatime3.c -o $(BIN_DIR)/charatatime3
	$(CC) $(CFLAG) exec.c -o $(BIN_DIR)/exec
	$(CC) $(CFLAG) system.c -o $(BIN_DIR)/system
	$(CC) $(CFLAG) genacct.c -o $(BIN_DIR)/genacct
	$(CC) $(CFLAG) pracct.c -o $(BIN_DIR)/pracct
	$(CC) $(CFLAG) printlogin.c -o $(BIN_DIR)/printlogin
	$(CC) $(CFLAG) nice.c -o $(BIN_DIR)/nice
	$(CC) $(CFLAG) printtimes.c -o $(BIN_DIR)/printtimes

.PHONY: clean

clean:
	$(RM) $(BIN_DIR)
