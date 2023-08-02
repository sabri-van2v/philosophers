#include "philo.h"

void    init_mutex_and_args(pthread_mutex_t *forks, t_philo *arg, t_data *data)
{
    int i;

    i = 0;
    pthread_mutex_init(&data->printer, NULL);
    while (i < data->number_of_philosophers)
        pthread_mutex_init(&forks[i++], NULL);
    i = 0;
    data->die = 0;
    while (i < data->number_of_philosophers)
    {
        arg[i].name = i + 1;
        arg[i].time_to_die = data->time_to_die;
        arg[i].time_to_eat = data->time_to_eat;
        arg[i].time_to_sleep = data->time_to_sleep;
        arg[i].must_eat = data->must_eat;
        arg[i].printer = &data->printer;
        arg[i].someone_die = &data->die;
        if (i != 0)
            (arg[i].forks)[0] = &forks[i - 1];
        else
            (arg[i].forks)[0] = &forks[data->number_of_philosophers - 1];
        (arg[i].forks)[1] = &forks[i];
        i++;
    }
}

void    destroy_mutex(pthread_mutex_t *forks, t_data *data)
{
    int i;

    i = 0;
    while (i < data->number_of_philosophers)
        pthread_mutex_destroy(&forks[i++]);
    pthread_mutex_destroy(&data->printer);
}

int    execute(t_data *data)
{
    pthread_t       *philos;
    pthread_mutex_t *forks;
    t_philo         *arg;

    philos = malloc(sizeof(pthread_t) * data->number_of_philosophers);
    forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
    arg = malloc(sizeof(t_philo) * data->number_of_philosophers);
    if (!philos || !forks || !arg)
        return (free(philos), free(forks), free(arg), 0);
    init_mutex_and_args(forks, arg, data);
    monitoring(data, philos, arg);
    destroy_mutex(forks, data);
    (free(philos), free(forks), free(arg));
    return (1);
}