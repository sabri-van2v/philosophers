#include <sys/time.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>

typedef struct s_thread
{
    pthread_mutex_t mutex;
    int             *index;
    pthread_t       thread;
}   t_mutex;

int security(char c)
{
    static int agent = 0;
    if (c == '+')
        agent++;
    return (agent);
}

void    *thread_f(void *data)
{
    t_mutex *secure = (t_mutex *)data;
    pthread_t my = secure->thread;

    while (security(' ') != my)
        ;
    pthread_mutex_lock(&(secure->mutex));
    printf("mutex lock by %lu\n", my);
    printf("%d\n", *(secure->index));
    (*secure->index)++;
    printf("index incremented by %lu, index : %d\n", my, *(secure->index));
    
    pthread_mutex_unlock(&(secure->mutex));
    security('+');
    printf("mutex unlock by %lu\n", my);
}

int main()
{
    pthread_t threads[5] = {0, 1, 2, 3, 4};
    t_mutex   secure[5];
    int        value = 0;

    pthread_mutex_init(&(secure[0].mutex), NULL);
    for (int i = 0; i < 5; i++)
    {
        secure[i].mutex = secure[0].mutex;
        secure[i].index = &value;
        secure[i].thread = threads[i];
        pthread_create(&threads[i], NULL, &thread_f, &secure[i]);
        usleep(200);  
    }
    pthread_join(threads[4], NULL);
    pthread_mutex_destroy(&(secure[0].mutex));
    printf("finish, the value is %d\n", *(secure[0].index));
}
