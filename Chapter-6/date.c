#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char const *argv[])
{
    time_t t;
    struct tm *tmp;
    char buf[64];

    time(&t);
    tmp = localtime(&t);
    if (strftime(buf, 64, "%c %Z", tmp) == 0) {
        perror("strftime failed: ");
        exit(1);
    } else {
        printf("%s\n", buf);
    }
    return 0;
}