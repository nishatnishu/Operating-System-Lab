#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;

void* threadFuncA(void* arg) {
    printf("Thread A: Trying to lock lock1...\n");
    pthread_mutex_lock(&lock1);
    printf("Thread A: lock1 acquired. Doing some work...\n");
    sleep(1);  

    printf("Thread A: Trying to lock lock2...\n");
    pthread_mutex_lock(&lock2);  

    printf("Thread A: Both locks acquired. Finishing up...\n");
    pthread_mutex_unlock(&lock2);
    pthread_mutex_unlock(&lock1);
    return NULL;
}

void* threadFuncB(void* arg) {
    printf("Thread B: Trying to lock lock2...\n");
    pthread_mutex_lock(&lock2);
    printf("Thread B: lock2 acquired. Doing some work...\n");
    sleep(1); 

    printf("Thread B: Trying to lock lock1...\n");
    pthread_mutex_lock(&lock1); 

    printf("Thread B: Both locks acquired. Finishing up...\n");
    pthread_mutex_unlock(&lock1);
    pthread_mutex_unlock(&lock2);
    return NULL;
}

int main() {
    pthread_t t1, t2;

    printf("Main: Starting deadlock simulation...\n");

    pthread_create(&t1, NULL, threadFuncA, NULL);
    pthread_create(&t2, NULL, threadFuncB, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

printf("Main: Program completed & No Deadlock happened!!😀\n");

    return 0;
}
