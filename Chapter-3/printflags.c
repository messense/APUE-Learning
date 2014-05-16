#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    int val;
    if (argc != 2) {
        printf("Usage: printflag <descriptor#>\n");
        exit(0);
    }
    if ((val = fcntl(atoi(argv[1]), F_GETFL, 0)) < 0) {
        fprintf(stderr, "fcntl error for fd %d\n", atoi(argv[1]));
        exit(1);
    }
    switch (val & O_ACCMODE) {
    case O_RDONLY:
        printf("read only");
        break;
    case O_WRONLY:
        printf("write only");
        break;
    case O_RDWR:
        printf("read write");
        break;
    default:
        fprintf(stderr, "unknown access mode\n");
        abort();
    }

    if (val & O_APPEND) {
        printf(", append");
    }
    if (val & O_NONBLOCK) {
        printf(", nonblocking");
    }
#if defined(O_SYNC)
    if (val & O_SYNC) {
        printf(", synchronous writes");
    }
#endif
#if !defined(_POSIX_C_SOURCE) && defined(O_FSYNC)
    if (val & O_FSYNC) {
        printf(", synchronous writes");
    }
#endif
    putchar('\n');
    return 0;
}