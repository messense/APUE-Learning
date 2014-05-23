#define _POSIX_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>
#include <time.h>
#include <errno.h>

static void pr_mask(const char *);
static void sig_usr1(int);
static void sig_alrm(int);
static sigjmp_buf jmpbuf;
static volatile sig_atomic_t canjump;

int main(int argc, char const *argv[])
{
    if (signal(SIGUSR1, sig_usr1) == SIG_ERR) {
        fprintf(stderr, "signal(SIGUSR1) error\n");
        exit(1);
    }
    if (signal(SIGALRM, sig_alrm) == SIG_ERR) {
        fprintf(stderr, "signal(SIGALRM) error\n");
        exit(1);
    }

    pr_mask("starting main: ");

    if (sigsetjmp(jmpbuf, 1)) {
        pr_mask("ending main: ");
        exit(0);
    }

    canjump = 1;

    for ( ; ; ) {
        pause();
    }

    return 0;
}

static void sig_usr1(int signo)
{
    time_t starttime;
    if (canjump == 0) {
        return;
    }
    pr_mask("starting sig_usr1: ");
    alarm(3);
    starttime = time(NULL);
    for ( ; ; ) {
        if (time(NULL) > starttime + 5)
        {
            break;
        }
    }
    pr_mask("finishing sig_usr1: ");
    canjump = 0;
    siglongjmp(jmpbuf, 1);
}

static void sig_alrm(int signo)
{
    pr_mask("in sig_alrm: ");
}

static void pr_mask(const char *str)
{
    sigset_t sigset;
    int errno_save;

    errno_save = errno;
    if (sigprocmask(0, NULL, &sigset) < 0) {
        fprintf(stderr, "sigprocmask error\n");
        return;
    }
    printf("%s ", str);
    if (sigismember(&sigset, SIGINT)) {
        printf("SIGINT");
    } else if (sigismember(&sigset, SIGQUIT)) {
        printf("SIGQUIT");
    } else if (sigismember(&sigset, SIGALRM)) {
        printf("SIGALRM");
    } else if (sigismember(&sigset, SIGUSR1)) {
        printf("SIGUSR1");
    } else if (sigismember(&sigset, SIGUSR2)) {
        printf("SIGUSR2");
    } else if (sigismember(&sigset, SIGABRT)) {
        printf("SIGABRT");
    } else if (sigismember(&sigset, SIGHUP)) {
        printf("SIGHUP");
    } else if (sigismember(&sigset, SIGCHLD)) {
        printf("SIGCHLD");
    }
    printf("\n");

    errno = errno_save;
}