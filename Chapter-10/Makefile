# c flag
CFLAG=-std=c99 -Wall
# delete files
RM=rm -rf
# create directory
MKDIR=-mkdir -p
# binary file directory
BIN_DIR=../bin/chapter-10

.PHONY: build

# make build
build:
	$(MKDIR) $(BIN_DIR)
	@echo Compiling chapter 10 codes...
	$(CC) $(CFLAG) sigusr.c -o $(BIN_DIR)/sigusr
	$(CC) $(CFLAG) myalarm.c -o $(BIN_DIR)/myalarm
	$(CC) $(CFLAG) sleep1.c -o $(BIN_DIR)/sleep1
	$(CC) $(CFLAG) sleep2.c -o $(BIN_DIR)/sleep2
	$(CC) $(CFLAG) sleep3.c -o $(BIN_DIR)/sleep3
	$(CC) $(CFLAG) timeout1.c -o $(BIN_DIR)/timeout1
	$(CC) $(CFLAG) timeout2.c -o $(BIN_DIR)/timeout2
	$(CC) $(CFLAG) printmask.c -o $(BIN_DIR)/printmask
	$(CC) $(CFLAG) sigpending.c -o $(BIN_DIR)/sigpending
	$(CC) $(CFLAG) signal.c -o $(BIN_DIR)/signal
	$(CC) $(CFLAG) sigsetjmp.c -o $(BIN_DIR)/sigsetjmp
	$(CC) $(CFLAG) sigsuspend1.c -o $(BIN_DIR)/sigsuspend1
	$(CC) $(CFLAG) sigsuspend2.c -o $(BIN_DIR)/sigsuspend2
	$(CC) $(CFLAG) abort.c -o $(BIN_DIR)/abort
	$(CC) $(CFLAG) system.c -o $(BIN_DIR)/system
	$(CC) $(CFLAG) sigtstp.c -o $(BIN_DIR)/sigtstp
	$(CC) $(CFLAG) signalnames.c -o $(BIN_DIR)/signalnames

.PHONY: clean

clean:
	$(RM) $(BIN_DIR)
