#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>

static jmp_buf env_alrm;

static void sig_alrm(int signo)
{
    longjmp(env_alrm, 1);
}

int my_sleep(int seconds)
{
    if (signal(SIGALRM, sig_alrm) == SIG_ERR) {
        return seconds;
    }
    if (setjmp(env_alrm) == 0) {
        alarm(seconds); /* start the timer */
        pause(); /* next caught signal wakes us up */
    }
    return alarm(0); /* turn off timer, return unslept time */
}

static void sig_int(int signo)
{
    int i, j;
    volatile int k = 0;
    /*
     * Tune these loops to run for more than 5 seconds
     * on whatever system this test program is run.
     */
    printf("\nsig_int starting\n");
    for (i = 0; i < 300000; i++) {
        for (j = 0; j < 4000; j++) {
            k += i * j;
        }
    }
    printf("sig_int finished\n");
}

int main(int argc, char const *argv[])
{
    int seconds;
    if (signal(SIGINT, sig_int) == SIG_ERR) {
        fprintf(stderr, "signal(SIGINT) error\n");
        exit(1);
    }
    seconds = my_sleep(5);
    printf("unslept time: %d\n", seconds);
    return 0;
}