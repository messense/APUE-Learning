#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

int system(const char *cmd)
{
    pid_t pid;
    int status;

    if (cmd == NULL) {
        return 1;
    }

    if ((pid = fork()) < 0) {
        status = -1;
    } else if (pid == 0) {
        execl("/bin/sh", "sh", "-c", cmd, (char *)0);
        _exit(127); /* execl error */
    } else {
        while (waitpid(pid, &status, 0) != pid) {
            if (errno != EINTR) {
                status = -1; /* error other than EINTR from waitpid() */
                break;
            }
        }
    }
    return status;
}

void pr_exit(int status)
{
    if (WIFEXITED(status))
        printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
        printf("abnormal termination, signal number = %d%s\n",
                WTERMSIG(status),
#ifdef  WCOREDUMP
                WCOREDUMP(status) ? " (core file generated)" : "");
#else
                "");
#endif
    else if (WIFSTOPPED(status))
    printf("child stopped, signal number = %d\n", WSTOPSIG(status));
}

int main(int argc, char const *argv[])
{
    int status;

    if ((status = system("date")) < 0) {
        fprintf(stderr, "system() error\n");
    }
    pr_exit(status);

    if ((status = system("nosuchcommand")) < 0) {
        fprintf(stderr, "system() error\n");
    }
    pr_exit(status);

    if ((status = system("who; exit 44")) < 0) {
        fprintf(stderr, "system() error\n");
    }
    pr_exit(status);

    return 0;
}