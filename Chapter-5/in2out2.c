#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1024

int main(int argc, char const *argv[])
{
    char buf[MAXLINE];
    while (fgets(buf, MAXLINE, stdin) != NULL) {
        if (fputs(buf, stdout) == EOF) {
            fprintf(stderr, "output error\n");
            exit(1);
        }
    }
    if (ferror(stdin)) {
        fprintf(stderr, "input error\n");
        exit(1);
    }
    return 0;
}