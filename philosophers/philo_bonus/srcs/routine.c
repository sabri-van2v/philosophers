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
    sem_wait(data->checker_philo);
    data->last_meal = get_time();
    sem_post(data->checker_philo);
    print_eat(data->name, data->start);
    usleep(data->time_to_eat * 1000);
}

void    is_sleeping(t_data *data)
{
    sem_post(data->forks);
    sem_post(data->forks);
    print_sleep(data->name, data->start);
    usleep(data->time_to_sleep * 1000);
}

void    is_thinking(t_data *data)
{
    print_think(data->name, data->start);
}

void    *monitoring_for_process(void *arg)
{
    t_data *data;
    data = (t_data *)arg;

    while (1)
    {
        sem_wait(data->checker_philo);
        if (data->all_finish)
            return (sem_post(data->checker_philo), NULL);
        if (get_time() - data->last_meal >= data->time_to_die)
        {
            sem_post(data->death);
            sem_close(data->checker_philo);
            sem_unlink("checker_philo");
            close_sem(data);
            free(data->philo);
            exit(1);
        }
        sem_post(data->checker_philo);
    }
    return (NULL);
}

void    routine(t_data *data)
{
    pthread_t   process_die;

    if (data->number_of_philosophers == 1)
        (take_forks(data), usleep(data->time_to_die * 1000), sem_post(data->death), destroy_sem(data), exit(1));
    sem_unlink("checker_philo");
    data->checker_philo = sem_open("checker_philo", O_CREAT, 0644, 1);
    pthread_create(&process_die, NULL, monitoring_for_process, data);
    while (data->must_eat)
    {
        take_forks(data);
        is_eating(data);
        is_sleeping(data);
        is_thinking(data);
        if (data->must_eat > 0)
            data->must_eat--;
    }
    sem_post(data->finish);
    sem_wait(data->checker_philo);
    data->all_finish = 1;
    sem_post(data->checker_philo);
    pthread_join(process_die, NULL);
    (destroy_sem(data), exit(0));
}