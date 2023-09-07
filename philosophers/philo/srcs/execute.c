#include "philo.h"

void    swap_order(pthread_mutex_t **a, pthread_mutex_t **b)
{
    pthread_mutex_t *tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}

void    init_mutex_and_args(pthread_mutex_t *forks, t_philo *arg, t_data *data)
{
    int i;

    i = 0;
    pthread_mutex_init(&data->death, NULL);
    pthread_mutex_init(&data->all_finish, NULL);
    pthread_mutex_init(&data->printer, NULL);
    while (i < data->number_of_philosophers)
        pthread_mutex_init(&forks[i++], NULL);
    i = 0;
    data->die = 0;
    data->finish = 0;
    while (i < data->number_of_philosophers)
    {
        arg[i].number_of_philosophers = data->number_of_philosophers;
        arg[i].name = i + 1;
        arg[i].time_to_die = data->time_to_die;
        arg[i].time_to_eat = data->time_to_eat;
        arg[i].time_to_sleep = data->time_to_sleep;
        arg[i].must_eat = data->must_eat;
        arg[i].printer = &data->printer;
        arg[i].death = &data->death;
        arg[i].all_finish = &data->all_finish;
        arg[i].someone_die = &data->die;
        arg[i].finish = &data->finish;
        pthread_mutex_init(&(arg[i].meal), NULL);
        if (i != 0)
            (arg[i].forks)[0] = &forks[i - 1];
        else
        {
            if (data->number_of_philosophers > 1)
                (arg[i].forks)[0] = &forks[data->number_of_philosophers - 1];
            else
                (arg[i].forks)[0] = NULL;
        }
        (arg[i].forks)[1] = &forks[i];
        if ((i + 1) % 2 == 0)
            swap_order(&((arg[i].forks)[0]), &((arg[i].forks)[1]));
        i++;
    }
}

void    destroy_mutex(pthread_mutex_t *forks, t_data *data, t_philo *arg)
{
    int i;

    i = 0;
    pthread_mutex_destroy(&data->death);
    pthread_mutex_destroy(&data->all_finish);
    pthread_mutex_destroy(&data->printer);
    while (i < data->number_of_philosophers)
        pthread_mutex_destroy(&forks[i++]);
    i = 0;
    while (i < data->number_of_philosophers)
        pthread_mutex_destroy(&(arg[i++].meal));
}

int    execute(t_data *data)
{
    pthread_t       *philos;
    pthread_mutex_t *forks;
    t_philo         *arg;
    int             successful_threads;

    philos = malloc(sizeof(pthread_t) * data->number_of_philosophers);
    forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
    arg = malloc(sizeof(t_philo) * data->number_of_philosophers);
    if (!philos || !forks || !arg)
        return (free(philos), free(forks), free(arg), 0);
    init_mutex_and_args(forks, arg, data);
    successful_threads = monitoring(data, philos, arg);
    join_philos(philos, successful_threads);
    destroy_mutex(forks, data, arg);
    (free(philos), free(forks), free(arg));
    return (1);
}