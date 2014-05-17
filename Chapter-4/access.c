#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char const *argv[])
{
    if (argc != 2) {
        printf("Usage: access <pathname>\n");
        exit(0);
    }
    if (access(argv[1], R_OK) < 0) {
        fprintf(stderr, "access error for %s: %s\n", argv[1], strerror(errno));
        exit(1);
    } else {
        printf("read access OK\n");
    }
    if (open(argv[1], O_RDONLY) < 0) {
        fprintf(stderr, "open error for %s: %s\n", argv[1], strerror(errno));
        exit(1);
    } else {
        printf("open for reading OK\n");
    }
    return 0;
}