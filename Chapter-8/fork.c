#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int globvar = 6; /* external variable in initialized data */
char buf[] = "a write to stdout\n";

int main(int argc, char const *argv[])
{
    int var; /* automatic variable on the stack */
    pid_t pid;
    var = 88;

    if (write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1) {
        fprintf(stderr, "write error\n");
        exit(1);
    }
    printf("before fork\n"); /* we don’t flush stdio */
    if ((pid = fork()) < 0) {
        fprintf(stderr, "fork error\n");
        exit(1);
    } else if (pid == 0) {
        /* child process */
        globvar++;
        var++;
    } else {
        /* parent process == current process */
        sleep(2);
    }
    printf("pid = %ld, globvar = %d, var = %d\n", (long)getpid(), globvar, var);
    return 0;
}