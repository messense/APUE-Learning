#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

char *env_init[] = { "USER=unknown", "PATH=/tmp", NULL };

int main(int argc, char const *argv[])
{
    pid_t pid;

    if ((pid = fork()) < 0) {
        fprintf(stderr, "fork error\n");
        exit(1);
    } else if (pid == 0) {
        // child process
        if (execle("/bin/echo", "echo", "myarg1", "MY ARG2", (char *)0, env_init) < 0) {
            /* specify pathname, specify environment */
            fprintf(stderr, "execle error\n");
            exit(1);
        }
    }
    if (waitpid(pid, NULL, 0) != pid) {
        fprintf(stderr, "waitpid error\n");
        exit(1);
    }

    if ((pid = fork()) < 0) {
        fprintf(stderr, "fork error\n");
        exit(1);
    } else if (pid == 0) {
        // child process
        if (execlp("echo", "echo", "only 1 arg", (char *)0) < 0) {
            /* specify filename, inherit environment */
            fprintf(stderr, "execlp error\n");
            exit(1);
        }
    }
    if (waitpid(pid, NULL, 0) != pid) {
        fprintf(stderr, "waitpid error\n");
        exit(1);
    }

    return 0;
}