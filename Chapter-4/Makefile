# c flag
CFLAG=-std=c99 -Wall
# delete files
RM=rm -rf
# create directory
MKDIR=-mkdir -p
# binary file directory
BIN_DIR=../bin/chapter-4

.PHONY: build

# make build
build:
	$(MKDIR) $(BIN_DIR)
	@echo Compiling chapter 4 codes...
	$(CC) $(CFLAG) printstat.c -o $(BIN_DIR)/printstat
	$(CC) $(CFLAG) access.c -o $(BIN_DIR)/access
	$(CC) $(CFLAG) umask.c -o $(BIN_DIR)/umask
	$(CC) $(CFLAG) chmod.c -o $(BIN_DIR)/chmod
	$(CC) $(CFLAG) unlink.c -o $(BIN_DIR)/unlink
	$(CC) $(CFLAG) futimens.c -o $(BIN_DIR)/futimens
	$(CC) $(CFLAG) ftw.c -o $(BIN_DIR)/ftw
	$(CC) $(CFLAG) chdir.c -o $(BIN_DIR)/chdir
	$(CC) $(CFLAG) getcwd.c -o $(BIN_DIR)/getcwd
	$(CC) $(CFLAG) printdev.c -o $(BIN_DIR)/printdev

.PHONY: clean

clean:
	$(RM) $(BIN_DIR)
