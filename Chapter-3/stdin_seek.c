#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    if (lseek(STDIN_FILENO, 0, SEEK_CUR) == -1)
    {
        fprintf(stderr, "Can not seek on stdin.\n");
    } else {
        printf("Seek OK on stdin.\n");
    }
    return 0;
}