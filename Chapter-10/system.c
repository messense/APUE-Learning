#define _POSIX_SOURCE
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

int system(const char *cmd)
{
    pid_t pid;
    int status;
    struct sigaction ignore, saveintr, savequit;
    sigset_t chldmask, savemask;

    if (cmd == NULL) {
        return 1;
    }

    /* ignore SIGINT and SIGQUIT */
    ignore.sa_handler = SIG_IGN;
    sigemptyset(&ignore.sa_mask);
    ignore.sa_flags = 0;

    if (sigaction(SIGINT, &ignore, &saveintr) < 0) {
        return -1;
    }
    if (sigaction(SIGQUIT, &ignore, &savequit) < 0) {
        return -1;
    }

    /* now block SIGCHLD */
    sigemptyset(&chldmask);
    sigaddset(&chldmask, SIGCHLD);
    if (sigprocmask(SIG_BLOCK, &chldmask, &savemask) < 0) {
        return -1;
    }

    if ((pid = fork()) < 0) {
        status = -1;
    } else if (pid == 0) {
        /* restore previous signal actions & reset signal mask */
        sigaction(SIGINT, &saveintr, NULL);
        sigaction(SIGQUIT, &savequit, NULL);
        sigprocmask(SIG_SETMASK, &savemask, NULL);

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

    /* restore previous signal actions & reset signal mask */
    if (sigaction(SIGINT, &saveintr, NULL) < 0) {
        return -1;
    }
    if (sigaction(SIGQUIT, &savequit, NULL) < 0) {
        return -1;
    }
    if (sigprocmask(SIG_SETMASK, &savemask, NULL) < 0) {
        return -1;
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