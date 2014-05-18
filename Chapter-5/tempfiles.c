#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1024

int main(void)
{
    char    name[L_tmpnam], line[MAXLINE];
    FILE    *fp;

    printf("%s\n", tmpnam(NULL));       /* first temp name */

    tmpnam(name);                       /* second temp name */
    printf("%s\n", name);

    if ((fp = tmpfile()) == NULL) {
        /* create temp file */
        fprintf(stderr, "tmpfile error\n");
        exit(1);
    }
    fputs("one line of output\n", fp);  /* write to temp file */
    rewind(fp);                         /* then read it back */
    if (fgets(line, sizeof(line), fp) == NULL) {
        fprintf(stderr, "fgets error\n");
        exit(1);
    }
    fputs(line, stdout);                /* print the line we wrote */

    return 0;
}