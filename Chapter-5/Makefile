# c flag
CFLAG=-std=c99 -Wall
# delete files
RM=rm -rf
# create directory
MKDIR=-mkdir -p
# binary file directory
BIN_DIR=../bin/chapter-5

.PHONY: build

# make build
build:
	$(MKDIR) $(BIN_DIR)
	@echo Compiling chapter 5 codes...
	$(CC) $(CFLAG) in2out1.c -o $(BIN_DIR)/in2out1
	$(CC) $(CFLAG) in2out2.c -o $(BIN_DIR)/in2out2
	$(CC) $(CFLAG) buf.c -o $(BIN_DIR)/buf
	$(CC) $(CFLAG) -Wno-deprecated-declarations tempfiles.c -o $(BIN_DIR)/tempfiles
	$(CC) $(CFLAG) mkstemp.c -o $(BIN_DIR)/mkstemp
	$(CC) $(CFLAG) memstr.c -o $(BIN_DIR)/memstr

.PHONY: clean

clean:
	$(RM) $(BIN_DIR)
