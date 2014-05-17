#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define FILE_NAME "tempfile"

int main(int argc, char const *argv[])
{
    if (open(FILE_NAME, O_CREAT | O_RDWR) < 0) {
        fprintf(stderr, "open error\n");
        exit(1);
    }
    if (unlink(FILE_NAME) < 0) {
        fprintf(stderr, "unlink error\n");
        exit(1);
    }
    printf("file unlinked\n");
    sleep(15);
    printf("done\n");
    return 0;
}