#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int c;
    while ((c = getc(stdin)) != EOF) {
        if (putc(c, stdout) == EOF) {
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