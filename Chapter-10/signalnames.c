#ifdef __linux
#define _BSD_SOURCE
#define _GNU_SOURCE
#define _XOPEN_SOURCE 700
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

int main(int argc, char const *argv[])
{
    // psignal
    psignal(SIGKILL, "SIGKILL");
    psignal(SIGINT, "SIGINT");
    psignal(SIGQUIT, "SIGQUIT");

    printf("\n");

    // strsignal
    printf("SIGKILL: %s\n", strsignal(SIGKILL));
    printf("SIGINT: %s\n", strsignal(SIGINT));
    printf("SIGQUIT: %s\n", strsignal(SIGQUIT));

    return 0;
}