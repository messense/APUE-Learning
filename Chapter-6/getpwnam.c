#define _BSD_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <errno.h>

struct passwd * my_getpwnam(const char *name) {
    struct passwd *ptr;
    setpwent(); // rewind first
    while ((ptr = getpwent()) != NULL) {
        if (strcmp(name, ptr->pw_name) == 0) {
            break;
        }
    }
    endpwent(); // close
    return ptr;
}

void print_passwd(const char *name) {
    errno = 0;
    struct passwd *pwd;
    pwd = my_getpwnam(name);
    if (pwd != NULL) {
        printf("User: %s\n", pwd->pw_name);
        printf("Home directory: %s\n", pwd->pw_dir);
        printf("Default shell: %s\n", pwd->pw_shell);
    } else {
        fprintf(stderr, "getpwnam error for %s", name);
        if (errno != 0) {
            perror("Error info: ");
        }
        putchar('\n');
    }
}

int main(int argc, char const *argv[])
{
    if (argc < 2) {
        printf("Usage: getpwnam <username>\n");
        exit(0);
    } 
    for (int i = 1; i < argc; ++i)
    {
        print_passwd(argv[i]);
    }
    return 0;
}