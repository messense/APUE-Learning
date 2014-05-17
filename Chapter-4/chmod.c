#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    struct stat buf;

    if (stat("foo", &buf) < 0) {
        fprintf(stderr, "stat error for foo\n");
        exit(1);
    }
    /* turn on set-group-id and turn off group-execute */
    if (chmod("foo", (buf.st_mode & ~S_IXGRP) | S_ISGID) < 0) {
        fprintf(stderr, "chmod error for foo\n");
        exit(1);
    }
    /* set absolute mode to rw-r--r-- */
    if (chmod("bar", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) < 0) {
        fprintf(stderr, "chmod error for bar\n");
        exit(1);
    }
    return 0;
}