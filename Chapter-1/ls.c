#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>

#define PATH_SIZE 1024

int main(int argc, char *argv[]) {
    DIR *dp = NULL;
    struct dirent *dirp = NULL;
    char *path = NULL;
    if (argc > 2) {
        printf("Usage: ls directory_name");
        exit(1);
    } else if (argc == 1) {
        path = (char *)malloc(PATH_SIZE);
        if (getcwd(path, PATH_SIZE) == NULL) {
            printf("getcwd failed!\n");
            exit(1);
        }
    } else {
        path = argv[1];
    } 

    if ((dp = opendir(path)) == NULL) {
        printf("can't open %s", path);
        exit(1);
    }

    while ((dirp = readdir(dp)) != NULL) {
        printf("%s\n", dirp->d_name);
    }

    closedir(dp);
    dp = NULL;
    if (argc == 1) {
        free(path);
    }

    return 0;
}
