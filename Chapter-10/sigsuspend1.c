#define _POSIX_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

static void pr_mask(const char *);
static void sig_int(int);

int main(int argc, char const *argv[])
{
    sigset_t newmask, oldmask, waitmask;
    pr_mask("program start: ");
    if (signal(SIGINT, sig_int) == SIG_ERR) {
        fprintf(stderr, "signal(SIGINT) error\n");
        exit(1);
    }
    sigemptyset(&waitmask);
    sigaddset(&waitmask, SIGUSR1);
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGINT);

    /*
     * Block SIGINT and save current signal mask.
     */
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
        fprintf(stderr, "sigprocmask(SIG_BLOCK) error\n");
        exit(1);
    }

    /*
     * Critical region of code.
     */
    pr_mask("in critical region: ");
    /*
     * Pause, allowing all signals except SIGUSR1.
     */
    if (sigsuspend(&waitmask) != -1) {
        fprintf(stderr, "sigsuspend error\n");
        exit(1);
    }
    pr_mask("after return from sigsuspend: ");
    /*
     * Reset signal mask which unblocks SIGINT.
     */
     if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
        fprintf(stderr, "sigprocmask(SIG_SETMASK) error\n");
        exit(1);
     }
     pr_mask("program exit: ");
    return 0;
}

static void sig_int(int signo)
{
    pr_mask("in sig_int: ");
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