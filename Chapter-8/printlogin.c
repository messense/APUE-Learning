#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    printf("%s\n", getlogin());
    return 0;
}