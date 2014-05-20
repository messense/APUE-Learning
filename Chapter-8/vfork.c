#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int globvar = 6; /* external variable in initialized data */

int main(int argc, char const *argv[])
{
    int var; /* automatic variable on the stack */
    pid_t pid;
    var = 88;

    printf("before fork\n"); /* we don’t flush stdio */
    if ((pid = vfork()) < 0) {
        fprintf(stderr, "vfork error\n");
        exit(1);
    } else if (pid == 0) {
        /* child process */
        globvar++;
        var++;
        _exit(0);
    }

    /* parent continues here */
    printf("pid = %ld, globvar = %d, var = %d\n", (long)getpid(), globvar, var);
    return 0;
}