#define _POSIX_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static void sig_quit(int signo)
{
    printf("caught SIGQUIT\n");
    if (signal(SIGQUIT, SIG_DFL) == SIG_ERR) {
        fprintf(stderr, "can't reset SIGQUIT\n");
        exit(1);
    }
}

int main(int argc, char const *argv[])
{
    sigset_t newmask, oldmask, pendmask;

    if (signal(SIGQUIT, sig_quit) == SIG_ERR) {
        fprintf(stderr, "can't catch SIGQUIT\n");
        exit(1);
    }

    /*
     * Block SIGQUIT and save current signal mask.
     */
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGQUIT);
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
        fprintf(stderr, "sigprocmask(SIG_BLOCK) error\n");
        exit(1);
    }

    sleep(5);   /* SIGQUIT here will remain pending */

    if (sigpending(&pendmask) < 0) {
        fprintf(stderr, "sigpending error\n");
        exit(1);
    }
    if (sigismember(&pendmask, SIGQUIT)) {
        printf("\nSIGQUIT pending\n");
    }

    /*
     * Restore signal mask which unblocks SIGQUIT.
     */
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
        fprintf(stderr, "sigprocmask(SIG_SETMASK) error\n");
        exit(1);
    }
    printf("SIGQUIT unblocked\n");
    sleep(5);   /* SIGQUIT here will terminate with core file */
    
    return 0;
}