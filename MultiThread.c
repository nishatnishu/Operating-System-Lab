#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 2
#define INCREMENTS 100000

int counter = 0;
pthread_mutex_t lock;

void* incrementWithoutLock(void* arg) {
    for (int i = 0; i < INCREMENTS; i++) {
        counter++; 
    }
    return NULL;
}

void* incrementWithLock(void* arg) {
    for (int i = 0; i < INCREMENTS; i++) {
        pthread_mutex_lock(&lock);
        counter++;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    printf(" Multithreading example with race condition (no mutex)...\n");

    counter = 0;
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, incrementWithoutLock, NULL);
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    printf(" Final counter without mutex: %d (Expected: %d)\n", counter, NUM_THREADS * INCREMENTS);

    printf("\n Multithreading example with mutex (thread-safe)...\n");

    counter = 0;
    pthread_mutex_init(&lock, NULL);
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, incrementWithLock, NULL);
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&lock);
    printf(" Final counter with mutex: %d (Expected: %d)\n", counter, NUM_THREADS * INCREMENTS);

    return 0;
}
