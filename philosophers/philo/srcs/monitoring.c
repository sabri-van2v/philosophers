#include "philo.h"

int create_all_philo(t_data *data, pthread_t *philos, t_philo *args)
{
    int i;

    i = -1;
    args[0].start = get_time();
    while (++i < data->number_of_philosophers)
    {
        args[i].start = args[0].start;
        args[i].last_meal = args[i].start;
        if (pthread_create(&philos[i], NULL, routine, &args[i]))
        {
            pthread_mutex_lock(&data->death);
            data->die = 1;
            pthread_mutex_unlock(&data->death);
            return (i);
        }
    }
    return (i);
}

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

int    monitoring(t_data *data, pthread_t *philos, t_philo *args)
{
    int i;
    int successful_threads;

    i = -1;
    args[0].start = get_time();
    successful_threads = create_all_philo(data, philos, args);
    if (successful_threads != data->number_of_philosophers)
        return (successful_threads);
    while (1)
    {
        pthread_mutex_lock(&data->all_finish);
        if (data->finish == data->number_of_philosophers)
            return (pthread_mutex_unlock(&data->all_finish), successful_threads);
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
                return (successful_threads);
            }
            i++;
        }
    }
    return (successful_threads);
}
