#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void	*fun_thread(void *arg)
{
	pthread_mutex_t	*mutex;

	mutex = (pthread_mutex_t *)arg;
	pthread_mutex_lock(mutex);
	printf("coucou\n");
	pthread_mutex_unlock(mutex);
	return(NULL);
}

int main()
{
	pthread_mutex_t	mutex;
	pthread_t	thread;

	thread = 0;
	pthread_mutex_init(&mutex, NULL);
	pthread_create(&thread, NULL, fun_thread, &mutex);
	pthread_join(thread, NULL);
	printf("yes\n");
	pthread_mutex_destroy(&mutex);
}