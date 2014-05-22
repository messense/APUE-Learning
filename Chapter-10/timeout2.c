#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>

#define MAXLINE 1024

static jmp_buf env_alrm;

static void sig_alrm(int signo)
{
    longjmp(env_alrm, 1);
}

int main(int argc, char const *argv[])
{
    int n;
    char line[MAXLINE];

    if (signal(SIGALRM, sig_alrm) == SIG_ERR) {
        fprintf(stderr, "signal(SIGALRM) error\n");
        exit(1);
    }
    if (setjmp(env_alrm) != 0) {
        printf("read timeout\n");
        exit(0);
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