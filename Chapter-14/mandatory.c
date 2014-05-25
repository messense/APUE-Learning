#define _POSIX_SOURCE
#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>

static volatile sig_atomic_t sigflag; /* set nonzero by sig handler */
static sigset_t newmask, oldmask, zeromask;

static void sig_usr(int signo)  /* one signal handler for SIGUSR1 and SIGUSR2 */
{
    sigflag = 1;
}

void TELL_WAIT(void)
{
    if (signal(SIGUSR1, sig_usr) == SIG_ERR) {
        fprintf(stderr, "signal(SIGUSR1) error\n");
        exit(1);
    }
    if (signal(SIGUSR2, sig_usr) == SIG_ERR) {
        fprintf(stderr, "signal(SIGUSR2) error\n");
        exit(1);
    }
    sigemptyset(&zeromask);
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGUSR1);
    sigaddset(&newmask, SIGUSR2);

    /* Block SIGUSR1 and SIGUSR2, and save current signal mask */
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
        fprintf(stderr, "SIG_BLOCK error\n");
        exit(1);
    }
}

void TELL_PARENT(pid_t pid)
{
    kill(pid, SIGUSR2);     /* tell parent we're done */
}

void WAIT_PARENT(void)
{
    while (sigflag == 0)
        sigsuspend(&zeromask);  /* and wait for parent */
    sigflag = 0;

    /* Reset signal mask to original value */
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
        fprintf(stderr, "SIG_SETMASK error\n");
        exit(1);
    }
}

void TELL_CHILD(pid_t pid)
{
    kill(pid, SIGUSR1);         /* tell child we're done */
}

void WAIT_CHILD(void)
{
    while (sigflag == 0)
        sigsuspend(&zeromask);  /* and wait for child */
    sigflag = 0;

    /* Reset signal mask to original value */
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
        fprintf(stderr, "SIG_SETMASK error\n");
        exit(1);
    }
}

int lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len)
{
    struct flock    lock;
    lock.l_type = type;     /* F_RDLCK, F_WRLCK, F_UNLCK */
    lock.l_start = offset;  /* byte offset, relative to l_whence */
    lock.l_whence = whence; /* SEEK_SET, SEEK_CUR, SEEK_END */
    lock.l_len = len;       /* #bytes (0 means to EOF) */
    return(fcntl(fd, cmd, &lock));
}

#define read_lock(fd, offset, whence, len) \
            lock_reg((fd), F_SETLK, F_RDLCK, (offset), (whence), (len))
#define write_lock(fd, offset, whence, len) \
            lock_reg((fd), F_SETLK, F_WRLCK, (offset), (whence), (len))

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

int main(int argc, char *argv[])
{
    int             fd;
    pid_t           pid;
    char            buf[5];
    struct stat     statbuf;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        exit(1);
    }
    if ((fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0) {
        fprintf(stderr, "open error\n");
        exit(1);
    }
    if (write(fd, "abcdef", 6) != 6) {
        fprintf(stderr, "write error\n");
        exit(1);
    }

    /* turn on set-group-ID and turn off group-execute */
    if (fstat(fd, &statbuf) < 0) {
        fprintf(stderr, "fstat error\n");
        exit(1);
    }
    if (fchmod(fd, (statbuf.st_mode & ~S_IXGRP) | S_ISGID) < 0) {
        fprintf(stderr, "fchmod error\n");
        exit(1);
    }

    TELL_WAIT();

    if ((pid = fork()) < 0) {
        fprintf(stderr, "fork error\n");
        exit(1);
    } else if (pid > 0) {   /* parent */
        /* write lock entire file */
        if (write_lock(fd, 0, SEEK_SET, 0) < 0) {
            fprintf(stderr, "write_lock error\n");
            exit(1);
        }

        TELL_CHILD(pid);

        if (waitpid(pid, NULL, 0) < 0) {
            fprintf(stderr, "waitpid error\n");
            exit(1);
        }
    } else {                /* child */
        WAIT_PARENT();      /* wait for parent to set lock */

        set_fl(fd, O_NONBLOCK);

        /* first let's see what error we get if region is locked */
        if (read_lock(fd, 0, SEEK_SET, 0) != -1) {   /* no wait */
            fprintf(stderr, "child: read_lock succeeded");
            exit(1);
        }
        printf("read_lock of already-locked region returns %d\n", errno);

        /* now try to read the mandatory locked file */
        if (lseek(fd, 0, SEEK_SET) == -1) {
            fprintf(stderr, "lseek error\n");
            exit(1);
        }
        if (read(fd, buf, 2) < 0) {
            printf("read failed (mandatory locking works)\n");
            return 1;
        } else {
            printf("read OK (no mandatory locking), buf = %2.2s\n", buf);
        }
    }
    return 0;
}