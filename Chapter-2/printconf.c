#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>

static void pr_sysconf(char *, int);
static void pr_pathconf(char *, const char *, int);

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("Usage: printconf <dirname>\n");
        exit(0);
    }
#ifdef ARG_MAX
    printf("ARG_MAX defined to be %d\n", ARG_MAX + 0);
#else
    printf("No symbol for ARG_MAX\n");
#endif
#ifdef _SC_ARG_MAX
    printf("ARG_MAX = %d\n", _SC_ARG_MAX + 0);
#else
    printf("No symbol for _SC_ARG_MAX\n");
#endif

/* similar processing for all the rest of the sysconf symbols... */

#ifdef MAX_CANON
    printf("MAX_CANON defined to be %d\n", MAX_CANON+0);
#else
    printf("no symbol for MAX_CANON\n");
#endif
#ifdef _PC_MAX_CANON
    pr_pathconf("MAX_CANON = ", argv[1], _PC_MAX_CANON);
#else
    printf("no symbol for _PC_MAX_CANON\n");
#endif

/* similar processing for all the rest of the pathconf symbols... */

    return 0;
}

static void pr_sysconf(char *mesg, int name)
{
    long val;

    fputs(mesg, stdout);
    errno = 0;
    if ((val = sysconf(name)) < 0) {
        if (errno != 0) {
            if (errno == EINVAL) {
                fputs(" (not supported)\n", stdout);
            } else {
                fprintf(stderr, "sysconf error\n");
            }
        } else {
            fputs(" (no limit)\n", stdout);
        }
    } else {
        printf(" %ld\n", val);
    }
}

static void pr_pathconf(char *mesg, const char *path, int name)
{
    long    val;

    fputs(mesg, stdout);
    errno = 0;
    if ((val = pathconf(path, name)) < 0) {
        if (errno != 0) {
            if (errno == EINVAL) {
                fputs(" (not supported)\n", stdout);
            } else {
                fprintf(stderr, "pathconf error, path = %s\n", path);
            }
        } else {
            fputs(" (no limit)\n", stdout);
        }
    } else {
        printf(" %ld\n", val);
    }
}
