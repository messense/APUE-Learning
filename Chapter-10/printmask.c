#define _POSIX_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

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
    } else {
        printf("Other signal types");
    }
    printf("\n");

    errno = errno_save;
}

int main(int argc, char const *argv[])
{
    pr_mask("Signal: ");
    return 0;
}