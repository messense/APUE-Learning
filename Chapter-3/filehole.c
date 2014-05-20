#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main(int argc, char const *argv[])
{
    int fd;
    if ((fd = creat("file.hole", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0) {
        fprintf(stderr, "creat error\n");
        exit(1);
    }
    if (write(fd, buf1, 10) != 10)
    {
        fprintf(stderr, "buf1 write error\n");
        exit(1);
    }
    /* offset now = 10 */
    if (lseek(fd, 16384, SEEK_SET) == -1)
    {
        fprintf(stderr, "lseek error\n");
        exit(1);
    }
    /* offset now = 16384 */
    if (write(fd, buf2, 10) != 10)
    {
        fprintf(stderr, "buf2 write error\n");
        exit(1);
    }
    /* offset now = 16394 */
    return 0;
}