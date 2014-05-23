#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static void sig_alrm(int signo)
{
    /* nothing to do, just return to wake up the pause */
}

unsigned int my_sleep(unsigned int seconds)
{
    if (signal(SIGALRM, sig_alrm) == SIG_ERR) {
        return seconds;
    }
    alarm(seconds); /* start the timer */
    pause(); /* next caught signal wakes us up */
    return alarm(0); /* turn off timer, return unslept time */
}

int main(int argc, char const *argv[])
{
    int seconds = my_sleep(5);
    printf("unslept time: %d\n", seconds);
    return 0;
}