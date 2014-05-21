#ifdef __linux
#define _POSIX_SOURCE
#endif
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>

static void sig_hup(int signo) {
    printf("SIGHUP received, pid = %ld\n", (long)getpid());
}

static void pr_ids(const char *name){
    printf("%s: pid = %ld, ppid = %ld, pgrp = %ld, tpgrp = %ld\n",
        name, (long)getpid(), (long)getppid(), (long)getpgrp(),
        (long)tcgetpgrp(STDIN_FILENO));
    fflush(stdout);
}

int main(int argc, char const *argv[])
{
    char c;
    pid_t pid;

    pr_ids("parent");
    if ((pid = fork()) < 0) {
        fprintf(stderr, "fork error\n");
        exit(1);
    } else if (pid == 0) {
        // child process
        pr_ids("child");
        signal(SIGHUP, sig_hup);    /* establish signal handler */
        kill(getpid(), SIGTSTP);    /* stop ourself */
        pr_ids("child");    /* prints only if we’re continued */
        if (read(STDIN_FILENO, &c, 1) != 1) {
            printf("read error %d on controlling TTY\n", errno);
        }
    } else {
        // current process
        sleep(5);
    }
    return 0;
}
