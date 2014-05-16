#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFSIZE 4096

static void sig_int(int);

int main(void) {
    char buf[BUFFSIZE];
    pid_t pid;
    int status;

    if (signal(SIGINT, sig_int) == SIG_ERR) {
        fprintf(stderr, "signal error.\n");
        exit(1);
    }

    printf("%% ");
    while (fgets(buf, BUFFSIZE, stdin) != NULL) {
        if (buf[strlen(buf) - 1] == '\n') {
            // replace newline with null
            buf[strlen(buf) - 1] = 0;
        }

        if ((pid = fork() < 0)) {
            fprintf(stderr, "fork error.\n");
            exit(1);
        } else if (pid == 0) {
            // child process
            if (execlp(buf, buf, NULL) < 0) {
                fprintf(stderr, "Couldn't execute: %s.\nexeclp faild: %s", buf, strerror(errno));
                exit(1);
            }
            exit(127);
        } else {
            // parent process
            if ((pid = waitpid(pid, &status, 0)) < 0) {
                fprintf(stderr, "waitpid error.\n");
                exit(1);
            }
        }

        printf("%% ");
    }
    return 0;
}

void sig_int(int signo) {
    printf("interrupt\n%% ");
}

