#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 10

typedef struct {
    int thread_id;
    int *shared_resource;
    pthread_mutex_t *mutex;
} thread_data;

void *thread_function(void *arg) {
    thread_data *data = (thread_data*)arg;
    int thread_id = data->thread_id;
    int *shared_resource = data->shared_resource;
    pthread_mutex_t *mutex = data->mutex;
    sleep(1);
    pthread_mutex_lock(mutex);
    sleep(1);
    printf("Thread %d has acquired the lock.\n", thread_id);
    sleep(1);
    (*shared_resource)++;
    printf("Thread %d incremented the shared resource to %d.\n", thread_id, *shared_resource);
    sleep(1);
    pthread_mutex_unlock(mutex);
    printf("Thread %d released the lock.\n", thread_id);
    sleep(1);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    thread_data thread_args[NUM_THREADS];
    int shared_resource = 0;
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_args[i].thread_id = i;
        thread_args[i].shared_resource = &shared_resource;
        thread_args[i].mutex = &mutex;
        pthread_create(&threads[i], NULL, thread_function, &thread_args[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("The final value of the shared resource is %d.\n", shared_resource);

    pthread_mutex_destroy(&mutex);

    return 0;
}
