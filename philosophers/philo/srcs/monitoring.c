#include "philo.h"

int ft_sleep_monitoring(t_data *data)
{
    int count;

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
        pthread_mutex_lock(&data->all_finish);
        if (data->finish == data->number_of_philosophers)
            return (pthread_mutex_unlock(&data->all_finish), 0);
        pthread_mutex_unlock(&data->all_finish);
    }
    return (1);
}

int philo_die(t_philo *arg, int i)
{
    pthread_mutex_lock(&(arg[i].meal));
    if (arg[i].must_eat != 0 && get_time() - arg[i].last_meal >= arg[i].time_to_die)
    {
        pthread_mutex_unlock(&arg[i].meal);
        return (1);
    }
    pthread_mutex_unlock(&(arg[i].meal));
    return (0);
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

    i = -1;
    checker = 0;
    call_printers();
    while (++i < data->number_of_philosophers)
    {
        args[i].last_meal = get_time();
        pthread_create(&philos[i], NULL, routine, &args[i]);
    }
    while (data->must_eat)
    {
        if (!ft_sleep_monitoring(data))
            break ;
        checker++;
        i = 0;
        while (i < data->number_of_philosophers)
        {
            if (philo_die(args, i))
            {
                pthread_mutex_lock(&data->death);
                data->die = 1;
                pthread_mutex_unlock(&data->death);
                pthread_mutex_lock(&data->printer);
                print_dead(i + 1);
                pthread_mutex_unlock(&data->printer);
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
