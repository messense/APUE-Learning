# c flag
CFLAG=-std=c99 -Wall -pthread
# delete files
RM=rm -rf
# create directory
MKDIR=-mkdir -p
# binary file directory
BIN_DIR=../bin/chapter-12
# platform
OS := $(shell uname)
ifeq ($(OS), Darwin)
	RTFLAG=
else
	RTFLAG=-Wl,--no-as-needed -lrt
endif

.PHONY: build

# make build
build:
	$(MKDIR) $(BIN_DIR)
	@echo Compiling chapter 12 codes...
	$(CC) $(CFLAG) detach.c -o $(BIN_DIR)/detach
	$(CC) $(CFLAG) timeout.c -o $(BIN_DIR)/timeout $(RTFLAG)
	$(CC) $(CFLAG) getenv1.c -o $(BIN_DIR)/getenv1
	$(CC) $(CFLAG) getenv2.c -o $(BIN_DIR)/getenv2
	$(CC) $(CFLAG) getenv3.c -o $(BIN_DIR)/getenv3
	$(CC) $(CFLAG) suspend.c -o $(BIN_DIR)/suspend
	$(CC) $(CFLAG) atfork.c -o $(BIN_DIR)/atfork

.PHONY: clean

clean:
	$(RM) $(BIN_DIR)
