#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    pid_t pid;
    if ((pid = fork()) < 0) {
        fprintf(stderr, "fork error\n");
        exit(1);
    } else if (pid == 0) {
        //first child process
        if ((pid = fork()) < 0) {
            fprintf(stderr, "fork error\n");
            exit(1);
        } else if (pid > 0) {
            /* parent from second fork == first child */
            exit(0);
        }
        /*
         * We’re the second child; our parent becomes init as soon
         * as our real parent calls exit() in the statement above.
         * Here’s where we’d continue executing, knowing that when
         * we’re done, init will reap our status.
         */
        sleep(2);
        printf("second child, parent pid = %ld\n", (long)getppid());
        exit(0);
    }

    if (waitpid(pid, NULL, 0) != pid) {
        fprintf(stderr, "waitpid error\n");
        exit(1);
    }
    /*
     * We’re the parent (the original process); we continue executing,
     * knowing that we’re not the parent of the second child.
     */
    return 0;
}