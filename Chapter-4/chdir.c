#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    if (chdir("/tmp") < 0) {
        fprintf(stderr, "chdir error for /tmp\n");
        exit(1);
    }
    printf("chdir to /tmp succeeded\n");
    return 0;
}