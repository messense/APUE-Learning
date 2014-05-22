#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <signal.h>

static void my_alarm(int signo)
{
    struct passwd *ptr;
    if ((ptr = getpwnam("root")) == NULL) {
        fprintf(stderr, "getpwnam(root) error\n");
        exit(1);
    }
    alarm(1);
}

int main(int argc, char const *argv[])
{
    struct passwd *ptr;
    signal(SIGALRM, my_alarm);

    alarm(1);
    for ( ; ; ) {
        if ((ptr = getpwnam("root")) == NULL) {
            fprintf(stderr, "getpwnam(root) error\n");
            exit(1);
        }
        if (strcmp(ptr->pw_name, "root") != 0) {
            printf("return value corrupted!, pw_name = %s\n", ptr->pw_name);
        }
    }
    return 0;
}