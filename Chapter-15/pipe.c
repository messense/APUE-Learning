#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define MAXLINE 1024

int main(int argc, char const *argv[])
{
    int fd[2];
    int n;
    char buf[MAXLINE];
    pid_t pid;

    if (pipe(fd) < 0) {
        fprintf(stderr, "pipe error\n");
        exit(1);
    }
    if ((pid = fork()) < 0) {
        fprintf(stderr, "fork error\n");
        exit(1);
    } else if (pid > 0) {
        close(fd[0]);
        write(fd[1], "hello world\n", 12);
    } else {
        close(fd[1]);
        n = read(fd[0], buf, MAXLINE);
        write(STDOUT_FILENO, buf, n);
    }
    return 0;
}