#include "philo.h"

int philo_die(t_philo *arg, int i)
{
    pthread_mutex_lock(&(arg[i].meal));
    if (get_time() - arg[i].last_meal >= arg[i].time_to_die)
    {
        pthread_mutex_unlock(&arg[i].meal);
        return (1);
    }
    pthread_mutex_unlock(&(arg[i].meal));
    return (0);
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

    i = -1;
    args[0].start = get_time();
    while (++i < data->number_of_philosophers)
    {
        args[i].start = args[0].start;
        args[i].last_meal = args[i].start;
        pthread_create(&philos[i], NULL, routine, &args[i]);
    }
    while (1)
    {
        pthread_mutex_lock(&data->all_finish);
        if (data->finish == data->number_of_philosophers)
            return ((void)pthread_mutex_unlock(&data->all_finish));
        pthread_mutex_unlock(&data->all_finish);
        i = 0;
        while (i < data->number_of_philosophers)
        {
            if (philo_die(args, i))
            {
                pthread_mutex_lock(&data->death);
                data->die = 1;
                pthread_mutex_unlock(&data->death);
                pthread_mutex_lock(&data->printer);
                print_dead(&args[i]);
                pthread_mutex_unlock(&data->printer);
                return ;
            }
            i++;
        }
    }
}
