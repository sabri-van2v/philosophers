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

void    join_philos(pthread_t *philos, int number)
{
    int i;

    i = 0;
    while (i < number)
        pthread_join(philos[i++], NULL);
}

void    monitoring(t_data *data, pthread_t *philos, t_philo *args)
{
    int i;
    int checker;
    int count;

    i = -1;
    checker = 0;
    data->start = get_time();
    init_last_meals(data->start, data->number_of_philosophers, args);
    call_printers();
    while (++i < data->number_of_philosophers)
        pthread_create(&philos[i], NULL, routine, &args[i]);
    while (data->must_eat)
    {
        count = data->time_to_die;
        while (count > 0)
        {
            if (count > 1000)
            {
                usleep(1000000);
                count -= 1000;
            }
            else
            {
                usleep(count * 1000);
                count = 0;
            }
            if (data->finish == data->number_of_philosophers)
                break ;
        }
        if (data->finish == data->number_of_philosophers)
            break ;
        checker++;
        i = 0;
        while (i < data->number_of_philosophers)
        {
            if ((get_time() - args[i].last_meal >= data->time_to_die * checker) && args[i].must_eat != 0)
            {
                data->die = 1;
                pthread_mutex_lock(&data->printer);
                print_dead(i + 1);
                join_philos(philos, data->number_of_philosophers);
                return ;
            }
            i++;
        }
        if (data->must_eat > 0)
            data->must_eat--;
    }
    join_philos(philos, data->number_of_philosophers);
}
