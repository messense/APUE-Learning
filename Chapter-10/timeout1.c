#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define MAXLINE 1024

static void sig_alrm(int signo)
{
    /* nothing to do, just return to interrupt the read */
}

int main(int argc, char const *argv[])
{
    int n;
    char line[MAXLINE];

    if (signal(SIGALRM, sig_alrm) == SIG_ERR) {
        fprintf(stderr, "signal(SIGALRM) error\n");
        exit(1);
    }
    alarm(10);
    if ((n = read(STDIN_FILENO, line, MAXLINE)) < 0) {
        fprintf(stderr, "read error\n");
        exit(1);
    }
    alarm(0);
    write(STDOUT_FILENO, line, n);
    return 0;
}