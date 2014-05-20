#define _BSD_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>

void make_temp(char *template);

int main(void)
{
    char good_template[] = "/tmp/dirXXXXXX"; /* right way */
    char *bad_template = "/tmp/dirXXXXXX";   /* wrong way*/

    printf("trying to create first temp file...\n");
    make_temp(good_template);
    printf("trying to create second temp file...\n");
    make_temp(bad_template);
    return 0;
}

void make_temp(char *template)
{
    int fd;
    struct stat sbuf;

    if ((fd = mkstemp(template)) < 0) {
        fprintf(stderr, "can't create temp file\n");
        exit(1);
    }
    printf("temp name = %s\n", template);
    close(fd);
    if (stat(template, &sbuf) < 0) {
        if (errno == ENOENT) {
            printf("file doesn't exist\n");
        } else {
            fprintf(stderr, "stat failed\n");
        exit(1);
        }
    } else {
        printf("file exists\n");
        unlink(template);
    }
}