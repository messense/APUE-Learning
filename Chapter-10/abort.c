#define _POSIX_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

/* POSIX-style abort() function */
void my_abort(void)
{
    sigset_t mask;
    struct sigaction action;

    /* Caller can’t ignore SIGABRT, if so reset to default */
    sigaction(SIGABRT, NULL, &action);
    if (action.sa_handler == SIG_IGN) {
        action.sa_handler = SIG_DFL;
        sigaction(SIGABRT, &action, NULL);
    }

    if (action.sa_handler == SIG_DFL) {
        /* flush all open stdio streams */
        fflush(NULL);
    }

    /* Caller can’t block SIGABRT; make sure it’s unblocked */
    sigfillset(&mask);
    sigdelset(&mask, SIGABRT);
    sigprocmask(SIG_SETMASK, &mask, NULL);

    /* send the signal */
    kill(getpid(), SIGABRT);

    /* If we’re here, process caught SIGABRT and returned */
    /* flush all open stdio streams */
    fflush(NULL);
    action.sa_handler = SIG_DFL;
    sigaction(SIGABRT, &action, NULL); /* reset to default */
    sigprocmask(SIG_SETMASK, &mask, NULL); /* just in case ... */
    kill(getpid(), SIGABRT); /* and one more time */
    exit(1); /* this should never be executed ... */
}

int main(int argc, char const *argv[])
{
    my_abort();
    return 0;
}