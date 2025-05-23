#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


struct ThreadData {
    int id;
    const char* message;
};

void* printThreadInfo(void* arg) {
    struct ThreadData* data = (struct ThreadData*) arg;

    for (int i = 1; i <= 3; i++) {
        printf("Thread %d: %s (Step %d)\n", data->id, data->message, i);
        sleep(1); 
    }

    printf("Thread %d: Finished my task!\n", data->id);
    return NULL;
}

int main() {
    pthread_t t1, t2;

    struct ThreadData d1 = {1, "Heeyyy! I'm Thread One:)"};
    struct ThreadData d2 = {2, "Helloo! I'm Thread Two:)"};

    printf("Main: Creating threads with parameters...\n");

    pthread_create(&t1, NULL, printThreadInfo, (void*)&d1);
    pthread_create(&t2, NULL, printThreadInfo, (void*)&d2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Main: Both threads have completed!!\n");
    return 0;
}

