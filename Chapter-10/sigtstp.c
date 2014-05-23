#define _POSIX_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define MAXLINE 1024

static void sig_tstp(int signo)
{
    sigset_t mask;
    /* ... move cursor to lower left corner, reset tty mode ... */

    /*
     * Unblock SIGTSTP, since it’s blocked while we’re handling it.
     */
    sigemptyset(&mask);
    sigaddset(&mask, SIGTSTP);
    sigprocmask(SIG_BLOCK, &mask, NULL);

    /* reset disposition to default */
    signal(SIGTSTP, SIG_DFL);

    /* and send the signal to ourself */
    kill(getpid(), SIGTSTP);

    /* we won’t return from the kill until we’re continued */
    /* reestablish signal handler */
    signal(SIGTSTP, sig_tstp);

    /* ... reset tty mode, redraw screen ... */
}

int main(int argc, char const *argv[])
{
    int n;
    char buf[MAXLINE];

    /*
     * Only catch SIGTSTP if we’re running with a job-control shell.
     */
    if (signal(SIGTSTP, SIG_IGN) == SIG_DFL) {
        signal(SIGTSTP, sig_tstp);
    }

    while ((n = read(STDIN_FILENO, buf, MAXLINE)) > 0) {
        if (write(STDOUT_FILENO, buf, n) != n) {
            fprintf(stderr, "write error\n");
            exit(1);
        }
    }

    if (n < 0) {
        fprintf(stderr, "read error\n");
        exit(1);
    }
    return 0;
}