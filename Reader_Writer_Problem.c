#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t rw_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int read_count = 0;
int data = 0;

void* reader(void* arg) {
    int id = *((int*)arg);
    
    pthread_mutex_lock(&mutex);
    read_count++;
    if (read_count == 1) {
        pthread_mutex_lock(&rw_mutex);
    }
    pthread_mutex_unlock(&mutex);

    printf("📖Reader %d is reading data = %d\n",id,data);
    sleep(1);

    pthread_mutex_lock(&mutex);
    read_count--;
    if (read_count==0) {
        pthread_mutex_unlock(&rw_mutex); 
    }
    pthread_mutex_unlock(&mutex);

    return NULL;
}

void* writer(void* arg) {
    int id = *((int*)arg);
    pthread_mutex_lock(&rw_mutex);
    data++;
    printf("✍️Writer %d is writing data = %d\n",id,data);
    sleep(1);
    
    pthread_mutex_unlock(&rw_mutex);
    
    return NULL;
}

int main() {
    pthread_t r[5],w[3];
    int i;
    int r_id[5] = {1,2,3,4,5};
    int w_id[3] = {1,2,3};

    for (i=0;i<3;i++) {
        pthread_create(&w[i],NULL,writer,&w_id[i]);
        pthread_create(&r[i],NULL,reader,&r_id[i]);
    }

    for (i=0;i<3;i++) {
        pthread_join(w[i],NULL);
        pthread_join(r[i],NULL);
    }
    return 0;
}
