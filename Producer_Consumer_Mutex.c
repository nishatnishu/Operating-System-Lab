#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define SIZE 5

int buffer[SIZE];
int in = 0, out = 0, count = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t notFull = PTHREAD_COND_INITIALIZER;
pthread_cond_t notEmpty = PTHREAD_COND_INITIALIZER;

void* producer(void* arg) {
    for (int i = 0; i < 10; i++) {
        int item = i + 1;

        pthread_mutex_lock(&mutex);
        while (count == SIZE)
            pthread_cond_wait(&notFull, &mutex);

        buffer[in] = item;
        printf("🏭Producer produced: %d\n", item);
        in = (in + 1) % SIZE;
        count++;

        pthread_cond_signal(&notEmpty);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    return NULL;
}

void* consumer(void* arg) {
    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&mutex);
        while (count == 0)
            pthread_cond_wait(&notEmpty, &mutex);

        int item = buffer[out];
        printf(" Consumer consumed: %d\n", item);
        out = (out + 1) % SIZE;
        count--;

        pthread_cond_signal(&notFull);
        pthread_mutex_unlock(&mutex);
        sleep(2);
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    return 0;
}
