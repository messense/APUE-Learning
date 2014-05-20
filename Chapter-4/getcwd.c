#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#ifdef __linux
#include <linux/limits.h>
#endif

int main(int argc, char const *argv[])
{
    size_t size = PATH_MAX + 1;
    char buf[size];

    if (chdir("/tmp") < 0) {
        fprintf(stderr, "chdir error for /tmp\n");
        exit(1);
    }
    if (getcwd(buf, size) == NULL) {
        fprintf(stderr, "getcwd failed.\n");
        exit(1);
    }
    printf("cwd = %s\n", buf);
    return 0;
}