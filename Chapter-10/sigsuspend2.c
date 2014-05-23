#define _POSIX_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

volatile sig_atomic_t quitflag = 0;

static void sig_int(int signo) {
    if (signo == SIGINT) {
        printf("\ninterrupt\n");
    } else if (signo == SIGQUIT) {
        quitflag = 1;
    }
}

int main(int argc, char const *argv[])
{
    sigset_t newmask, oldmask, zeromask;
    if (signal(SIGINT, sig_int) == SIG_ERR) {
        fprintf(stderr, "signal(SIGINT) error\n");
        exit(1);
    }
    if (signal(SIGQUIT, sig_int) == SIG_ERR) {
        fprintf(stderr, "signal(SIGQUIT) error\n");
        exit(1);
    }

    sigemptyset(&zeromask);
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGQUIT);

    /*
     * Block SIGQUIT and save current signal mask.
     */
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask)< 0) {
        fprintf(stderr, "sigprocmask(SIG_BLOCK) error\n");
        exit(1);
    }

    while (quitflag == 0) {
        sigsuspend(&zeromask);
    }

    /*
     * SIGQUIT has been caught and is now blocked; do whatever.
     */
    quitflag = 0;

    /*
     * Reset signal mask which unblocks SIGQUIT.
     */
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
        fprintf(stderr, "sigprocmask(SIG_SETMASK) error\n");
        exit(1);
    }
    return 0;
}