#include <stdio.h>
#include <pthread.h>

void *th1(void *arg) {
    for (int i = 0; i < 100; i++) {
        printf("Thread 1: %d\n", i);
    }
}

void *th2(void *arg) {
    for (int i = 0; i < 100; i++) {
        printf("Thread 2: %d\n", i);
    }
}

int main(void) {
    pthread_t t1;
    pthread_t t2;

    pthread_create(&t1, NULL, th1, NULL);
    pthread_create(&t2, NULL, th2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}