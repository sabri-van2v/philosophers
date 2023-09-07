#include "philo_bonus.h"

void    take_forks(t_data *data)
{
    usleep(1000);
    if (data->number_of_philosophers > 1)
    {
        sem_wait(data->forks);
        print_fork(data->name, data->start);
    }
    sem_wait(data->forks);
    print_fork(data->name, data->start);
}

void    is_eating(t_data *data)
{
    data->last_meal = get_time();
    print_eat(data->name, data->start);
    // printf("e %d\n", data->time_to_eat);
    sleep_philo(data, data->time_to_eat);
}

void    is_sleeping(t_data *data)
{
    sem_post(data->forks);
    sem_post(data->forks);
    print_sleep(data->name, data->start);
    // printf("s %d\n", data->time_to_sleep);
    sleep_philo(data, data->time_to_sleep);
}

void    is_thinking(t_data *data)
{
    print_think(data->name, data->start);
    // printf("%d\n", data->time_to_die);
    // sleep_philo(data, data->time_to_die - (get_time() - data->last_meal));
}

void    monitoring_for_process(t_data *data)
{
    if (get_time() - data->last_meal >= data->time_to_die)
    {
        sem_post(data->death);
        close_sem(data);
        free(data->philo);
        exit(1);
    }
}

void    routine(t_data *data)
{
    if (data->number_of_philosophers == 1)
        (take_forks(data), usleep(data->time_to_die * 1000), sem_post(data->death), destroy_sem(data), exit(1));
    while (1)
    {
        take_forks(data);
        monitoring_for_process(data);
        is_eating(data);
        if (data->must_eat >= 0)
        {
            data->must_eat--;
            if (data->must_eat == 0)
                sem_post(data->finish);
        }
        monitoring_for_process(data);
        is_sleeping(data);
        monitoring_for_process(data);
        is_thinking(data);
        monitoring_for_process(data);
    }
    (destroy_sem(data), exit(0));
}