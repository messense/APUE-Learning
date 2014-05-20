#define _BSD_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#ifdef SOLARIS
#include <sys/mkdev.h>
#endif

int main(int argc, char const *argv[])
{
    struct stat buf;
    for (int i = 1; i < argc; ++i)
    {
        printf("%s: ", argv[i]);
        if (stat(argv[i], &buf) < 0) {
            fprintf(stderr, "stat error for %s\n", argv[i]);
            continue;
        }
        printf("dev = %d/%d", major(buf.st_dev),  minor(buf.st_dev));
        if (S_ISCHR(buf.st_mode) || S_ISBLK(buf.st_mode)) {
            printf(" (%s) rdev = %d/%d", (S_ISCHR(buf.st_mode)) ? "character" : "block", major(buf.st_rdev), minor(buf.st_rdev));
        }
        printf("\n");
    }
    return 0;
}