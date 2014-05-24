#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int makethread(void *(*fn)(void *), void *arg)
{
    int err;
    pthread_t tid;
    pthread_attr_t attr;

    err = pthread_attr_init(&attr);
    if (err != 0) {
        return err;
    }
    err = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if (err == 0) {
        err = pthread_create(&tid, &attr, fn, arg);
    }
    pthread_attr_destroy(&attr);
    return err;
}

void * thr_fn(void *arg)
{
    printf("detached thread 1\n");
    return (void *)0;
}

int main(int argc, char const *argv[])
{
    makethread(thr_fn, NULL);
    return 0;
}