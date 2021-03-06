APUE-Learning
=============

[![Build Status](https://travis-ci.org/messense/APUE-Learning.svg?branch=master)](https://travis-ci.org/messense/APUE-Learning)

Codes I wrote when learning Advanced Programming in the UNIX Environment 3rd edition.

The `apue.h` introduced in the book is not used by these codes for simplicity and readability. All the codes are built and tested on OS X 10.9 with LLVM clang and Ubuntu 12.04 LTS with GCC 4.6.3.

## Table of contents

- [X] [Chapter 1.   UNIX System Overview](Chapter-1/)
- [X] [Chapter 2.  UNIX Standardization and Implementations](Chapter-2/)
- [X] [Chapter 3.  File I/O](Chapter-3)
- [X] [Chapter 4.  Files and Directories](Chapter-4)
- [X] [Chapter 5.  Standard I/O Library](Chapter-5)
- [X] [Chapter 6.  System Data Files and Information](Chapter-6)
- [X] [Chapter 7.  Process Environment](Chapter-7)
- [X] [Chapter 8.  Process Control](Chapter-8)
- [X] [Chapter 9.  Process Relationships](Chapter-9)
- [X] [Chapter 10.  Signals](Chapter-10)
- [X] [Chapter 11.  Threads](Chapter-11)
- [X] [Chapter 12.  Thread Control](Chapter-12)
- [X] [Chapter 13.  Daemon Processes](Chatper-13)
- [ ] [Chapter 14.  Advanced I/O](Chapter-14)
- [ ] [Chapter 15.  Interprocess Communication](Chapter-15)
- [ ] Chapter 16.  Network IPC: Sockets
- [ ] Chapter 17.  Advanced IPC
- [ ] Chapter 18.  Terminal I/O
- [ ] Chapter 19.  Pseudo Terminals
- [ ] Chapter 20.  A Database Library
- [ ] Chapter 21.  Communicating with a Network Printer

## How to build

Simply run `make` or enter a specific chapter directory and run `make` to build binaries for that chapter. Executable binaries will be found inside `bin/` directory categorized by chapter.

## License

The MIT License (MIT)

Copyright (c) 2014 messense

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
