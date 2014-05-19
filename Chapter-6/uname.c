#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/utsname.h>

#define HOST_NAME_MAX 256

int main(int argc, char const *argv[])
{
    struct utsname un;
    char hostname[HOST_NAME_MAX];

    if (uname(&un) == -1) {
        perror("uname failed: ");
        exit(1);
    }
    printf("System name: %s\n", un.sysname);
    printf("Network name: %s\n", un.nodename);
    printf("Release level: %s\n", un.release);
    printf("OS version: %s\n", un.version);
    printf("Hardware platform: %s\n", un.machine);

    if (gethostname(hostname, HOST_NAME_MAX) == 0) {
        printf("Hostname: %s\n", hostname);
    }
    return 0;
}