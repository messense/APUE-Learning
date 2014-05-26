#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <aio.h>

#define BSZ 4096
#define NBUF 8

enum rwop {
    UNUSED = 0,
    READ_PENDING = 1,
    WRITE_PENDING = 2
};

struct buf {
    enum rwop     op;
    int           last;
    struct aiocb  aiocb;
    unsigned char data[BSZ];
};

struct buf bufs[NBUF];

unsigned char translate(unsigned char c)
{
    if (isalpha(c)) {
        if (c >= 'n')
            c -= 13;
        else if (c >= 'a')
            c += 13;
        else if (c >= 'N')
            c -= 13;
        else
            c += 13;
    }
    return(c);
}

int main(int argc, char* argv[])
{
    int                 ifd, ofd, i, j, n, err, numop;
    struct stat         sbuf;
    const struct aiocb  *aiolist[NBUF];
    off_t               off = 0;

    if (argc != 3) {
        printf("Usage: %s infile outfile\n", argv[0]);
        exit(0);
    }
    if ((ifd = open(argv[1], O_RDONLY)) < 0) {
        fprintf(stderr, "can't open %s\n", argv[1]);
        exit(1);
    }
    if ((ofd = open(argv[2], O_RDWR|O_CREAT|O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0) {
        fprintf(stderr, "can't create %s\n", argv[2]);
        exit(1);
    }
    if (fstat(ifd, &sbuf) < 0) {
        fprintf(stderr, "fstat failed\n");
        exit(1);
    }

    /* initialize the buffers */
    for (i = 0; i < NBUF; i++) {
        bufs[i].op = UNUSED;
        bufs[i].aiocb.aio_buf = bufs[i].data;
        bufs[i].aiocb.aio_sigevent.sigev_notify = SIGEV_NONE;
        aiolist[i] = NULL;
    }

    numop = 0;
    for (;;) {
        for (i = 0; i < NBUF; i++) {
            switch (bufs[i].op) {
            case UNUSED:
                /*
                 * Read from the input file if more data
                 * remains unread.
                 */
                if (off < sbuf.st_size) {
                    bufs[i].op = READ_PENDING;
                    bufs[i].aiocb.aio_fildes = ifd;
                    bufs[i].aiocb.aio_offset = off;
                    off += BSZ;
                    if (off >= sbuf.st_size)
                        bufs[i].last = 1;
                    bufs[i].aiocb.aio_nbytes = BSZ;
                    if (aio_read(&bufs[i].aiocb) < 0) {
                        fprintf(stderr, "aio_read failed\n");
                    }
                    aiolist[i] = &bufs[i].aiocb;
                    numop++;
                }
                break;

            case READ_PENDING:
                if ((err = aio_error(&bufs[i].aiocb)) == EINPROGRESS)
                    continue;
                if (err != 0) {
                    if (err == -1) {
                        fprintf(stderr, "aio_error failed\n");
                        exit(1);
                    } else {
                        fprintf(stderr, "read failed\n");
                        exit(0);
                    }
                }

                /*
                 * A read is complete; translate the buffer
                 * and write it.
                 */
                if ((n = aio_return(&bufs[i].aiocb)) < 0) {
                    fprintf(stderr, "aio_return failed\n");
                    exit(1);
                }
                if (n != BSZ && !bufs[i].last) {
                    printf("short read (%d/%d)\n", n, BSZ);
                    exit(0);
                }
                for (j = 0; j < n; j++)
                    bufs[i].data[j] = translate(bufs[i].data[j]);
                bufs[i].op = WRITE_PENDING;
                bufs[i].aiocb.aio_fildes = ofd;
                bufs[i].aiocb.aio_nbytes = n;
                if (aio_write(&bufs[i].aiocb) < 0) {
                    fprintf(stderr, "aio_write failed\n");
                    exit(1);
                }
                /* retain our spot in aiolist */
                break;

            case WRITE_PENDING:
                if ((err = aio_error(&bufs[i].aiocb)) == EINPROGRESS)
                    continue;
                if (err != 0) {
                    if (err == -1) {
                        fprintf(stderr, "aio_error failed\n");
                        exit(1);
                    } else {
                        fprintf(stderr, "write failed\n");
                        exit(1);
                    }
                }

                /*
                 * A write is complete; mark the buffer as unused.
                 */
                if ((n = aio_return(&bufs[i].aiocb)) < 0) {
                    fprintf(stderr, "aio_return failed\n");
                    exit(1);
                }
                if (n != bufs[i].aiocb.aio_nbytes) {
                    printf("short write (%d/%d)\n", n, BSZ);
                    exit(0);
                }
                aiolist[i] = NULL;
                bufs[i].op = UNUSED;
                numop--;
                break;
            }
        }
        if (numop == 0) {
            if (off >= sbuf.st_size)
                break;
        } else {
            if (aio_suspend(aiolist, NBUF, NULL) < 0) {
                fprintf(stderr, "aio_suspend failed\n");
                exit(1);
            }
        }
    }

    bufs[0].aiocb.aio_fildes = ofd;
    if (aio_fsync(O_SYNC, &bufs[0].aiocb) < 0) {
        fprintf(stderr, "aio_fsync failed\n");
        exit(1);
    }
    return 0;
}