#ifndef __APPLE__
#define _GNU_SOURCE
#define _XOPEN_SOURCE 700
#endif
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>

/* Mac OS X does not have futimens */

int main(int argc, char const *argv[])
{
    int fd;
    struct stat buf;
#ifdef __APPLE__
    struct timeval times[2];
#else
    struct timespec times[2];
#endif

    for (int i = 1; i < argc; ++i)
    {
        if (stat(argv[i], &buf) < 0) {
            fprintf(stderr, "stat error for %s\n", argv[i]);
            continue;
        }
        if ((fd = open(argv[i], O_RDWR | O_TRUNC)) < 0) {
            fprintf(stderr, "open error for %s\n", argv[i]);
            continue;
        }
#ifdef __APPLE__
        times[0].tv_sec = buf.st_atimespec.tv_sec; // access time
        times[0].tv_usec = buf.st_atimespec.tv_nsec * 1000;
        times[1].tv_sec = buf.st_mtimespec.tv_sec; // modification time
        times[1].tv_usec = buf.st_mtimespec.tv_nsec * 1000;
        if (futimes(fd, times) < 0) {
            /* reset times */
            fprintf(stderr, "futimes error for %s\n", argv[i]);
        }
#else
        times[0].tv_sec = buf.st_atime; // access time
        times[0].tv_nsec = 0;
        times[1].tv_sec = buf.st_mtime; // modification time
        times[1].tv_nsec = 0;
        if (futimens(fd, times) < 0) {
            /* reset times */
            fprintf(stderr, "futimens error for %s\n", argv[i]);
        }
#endif
        close(fd);
    }
    return 0;
}