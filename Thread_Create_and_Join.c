#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* sayHello(void* arg) {
    for (int i=1;i<=5;i++) {
        printf("🧵Thread: Hello! Count %d\n",i);
        sleep(1); 
    }
    printf("Thread:I'm done with my job.Exiting now!\n");
    return NULL;
}

int main() {
    pthread_t thread;

    printf("Main: Creating a thread...\n");
    pthread_create(&thread,NULL,sayHello,NULL);

    for (int j=1;j<=3;j++) {
        printf("Main: Doing some work... Step %d\n",j);
        sleep(1);
    }

    pthread_join(thread,NULL);
    printf("✅Main: Thread has completed and joined back.\n");

    return 0;
}
