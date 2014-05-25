#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

/* flags are file status flags to turn on */
void set_fl(int fd, int flags)
{
    int val;

    if ((val = fcntl(fd, F_GETFL, 0)) < 0) {
        fprintf(stderr, "fcntl F_GETFL error");
        exit(1);
    }

    val |= flags;       /* turn on flags */

    if (fcntl(fd, F_SETFL, val) < 0) {
        fprintf(stderr, "fcntl F_SETFL error");
        exit(1);
    }
}

/* flags are the file status flags to turn off */
void clr_fl(int fd, int flags)
{
    int     val;

    if ((val = fcntl(fd, F_GETFL, 0)) < 0) {
        fprintf(stderr, "fcntl F_GETFL error");
        exit(1);
    }

    val &= ~flags;      /* turn flags off */

    if (fcntl(fd, F_SETFL, val) < 0) {
        fprintf(stderr, "fcntl F_SETFL error");
        exit(1);
    }
}

int main(int argc, char const *argv[])
{
    int ntowrite, nwrite;
    char *ptr;
    char buf[50000];

    ntowrite = read(STDIN_FILENO, buf, sizeof(buf));
    fprintf(stderr, "read %d bytes\n", ntowrite);

    /* set nonblocking */
    set_fl(STDOUT_FILENO, O_NONBLOCK);

    ptr = buf;
    while (ntowrite > 0) {
        errno = 0;
        nwrite = write(STDOUT_FILENO, ptr, ntowrite);
        fprintf(stderr, "nwrite = %d, errno = %d\n", nwrite, errno);
        if (nwrite > 0) {
            ptr += nwrite;
            ntowrite -= nwrite;
        }
    }
    /* clear nonblocking */
    clr_fl(STDOUT_FILENO, O_NONBLOCK);
    return 0;
}