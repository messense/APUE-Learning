#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    for (int i = 0; i < argc; ++i)
    {
        printf("argv[%d]: %s\n", i, argv[i]);
    }
    return 0;
}