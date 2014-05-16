#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>

#ifdef OPNE_MAX
static long openmax = OPNE_MAX;
#else
static long openmax = 0;
#endif

#define OPNE_MAX_GUESS 256

long open_max(void) {
    if (openmax == 0) {
        errno = 0;
        if ((openmax = sysconf(_SC_OPEN_MAX)) < 0) {
            if (errno == 0) {
                openmax = OPNE_MAX_GUESS;
            } else {
                fprintf(stderr, "sysconf error for _SC_OPEN_MAX\n");
            }
        }
    }
    return openmax;
}

int main(int argc, char const *argv[])
{
    printf("Open max = %ld\n", open_max());
    return 0;
}