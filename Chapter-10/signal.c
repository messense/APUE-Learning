#define _POSIX_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

typedef void SignalHandler(int);

/* Reliable version of signal(), using POSIX sigaction().  */
SignalHandler * my_signal(int signo, SignalHandler *handler)
{
    struct sigaction act, oact;
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    if (signo == SIGALRM) {
#ifdef  SA_INTERRUPT
        act.sa_flags |= SA_INTERRUPT;
#endif
    } else {
#ifdef SA_RESTART
        act.sa_flags |= SA_RESTART;
#endif
    }
    if (sigaction(signo, &act, &oact) < 0) {
        return SIG_ERR;
    }
    return act.sa_handler;
}

void sig_quit(int signo)
{
    printf("Caught SIGQUIT.\n");
}

int main(int argc, char const *argv[])
{
    if (my_signal(SIGQUIT, sig_quit) == SIG_ERR) {
        fprintf(stderr, "my_signal(SIGQUIT) error\n");
        exit(1);
    }
    for (int i = 0; i < 1000; ++i)
    {
        sleep(1);
    }
    return 0;
}