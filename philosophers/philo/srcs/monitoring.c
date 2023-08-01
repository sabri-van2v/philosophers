#include "philo.h"

void    init_last_meals(long start, int number, t_philo *args)
{
    int i;

    i = 0;
    while (i < number)
        args[i++].last_meal = start;
}

void    call_printers()
{
    print_fork(0);
    print_eat(0);
    print_sleep(0);
    print_think(0);
    print_dead(0);
}

void    join_philos(pthread_t *philo, int number)
{
    int i;

    i = 0;
    while (i < number)
        pthread_join(philo[i++], NULL);
}

void    monitoring(t_data *data, pthread_t *philos, t_philo *args)
{
    int i;
    int checker;

    i = -1;
    checker = 0;
    data->start = get_time();
    init_last_meals(data->start, data->number_of_philosophers, args);
    call_printers();
    while (++i < data->number_of_philosophers)
        pthread_create(&philos[i], NULL, routine, &args[i]);
    while (data->must_eat)
    {
        usleep(data->time_to_die * 1000);
        i = 0;
        while (i < data->number_of_philosophers)
        {
            // printf("last_meal [ %d ] : %lu\n", i, args[i].last_meal);
            // printf("data->sta [ %d ] : %lu\n", i, data->start);
            // printf("diff [ %d ] : %lu\n", i, args[i].last_meal - data->start);
            //printf("tdie [ %d ] : %d\n", i, data->time_to_die * checker);
            if (args[i].last_meal - data->start > data->time_to_die * checker)
            {
                data->die = 1;
                usleep(1000);
                pthread_mutex_lock(&data->printer);
                print_dead(i + 1);
                join_philos(philos, data->number_of_philosophers);
                return ;
            }
            i++;
        }
        checker++;
        if (data->must_eat > 0)
            data->must_eat--;
    }
}