#include "philo_bonus.h"

void    init_semaphore(t_data *data)
{
    if ((data->forks = sem_open("forks", O_CREAT, 0644, data->number_of_philosophers)) == SEM_FAILED
        || (data->finish = sem_open("finish", O_CREAT, 0644, 0)) == SEM_FAILED
        || (data->checker = sem_open("checker", O_CREAT, 0644, 1)) == SEM_FAILED
        || (data->death = sem_open("death", O_CREAT, 0644, 0)) == SEM_FAILED)
        (destroy_sem(data), exit(1));
}

void    create_philos(t_data *data)
{
    int i;

    i = 0;
    data->start = get_time();
    data->last_meal = data->start;
    while (i < data->number_of_philosophers)
    {
        data->philo[i] = fork();
        if (data->philo[i] == -1)
            write(2, "fork failed\n", 12);
        if (data->philo[i] == 0)
        {
            data->name = i + 1;
            if (data->name % 2 == 0)
                usleep(data->time_to_eat * 1000);
            routine(data);
        }
        i++;
    }
}

void    execute(t_data *data)
{
    data->philo = malloc(sizeof(pid_t) * data->number_of_philosophers);
    if (!data->philo)
        exit(1);
    init_semaphore(data);
    create_philos(data);
    //monitoring(data);
    destroy_sem(data);
}