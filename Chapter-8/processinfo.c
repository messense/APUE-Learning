#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
    printf("Process ID: %d\n", getpid());
    printf("Parent Process ID: %d\n", getppid());
    printf("Real User ID: %u\n", getuid());
    printf("Effective User ID: %u\n", geteuid());
    printf("Real Group ID: %u\n", getgid());
    printf("Effective Group ID: %u\n", getegid());
    return 0;
}