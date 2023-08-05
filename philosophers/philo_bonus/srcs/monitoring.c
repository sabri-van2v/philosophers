#include "philo_bonus.h"

void    wait_philo(int number)
{
    int i;

    i = 0;
    while (i < number)
    {
        waitpid(-1, NULL, 0);
        i++;
    }
}

void    *check_all_finish(void *arg)
{
    t_data *data;
    data = (t_data *)arg;
    int i;

    i = 0;
    while (1)
    {
        if (i == data->number_of_philosophers)
            break ;
        sem_wait(data->finish);
        i++;
    }
    sem_wait(data->checker);
    data->all_finish = 1;
    sem_post(data->checker);
    return (NULL);
}

void    *check_one_death(void *arg)
{
    t_data *data;
    data = (t_data *)arg;

    sem_wait(data->death);
    sem_wait(data->checker);
    data->die = 1;
    sem_post(data->checker);
    return (NULL);
}

int ft_sleep_monitoring(t_data *data)
{
    while (1)
    {
        usleep(1000);
        sem_wait(data->checker);
        if (data->die)
            return (sem_post(data->checker), 2);
        if (data->all_finish)
            return (sem_post(data->checker), 0);
        sem_post(data->checker);
    }
    return (1);
}

int   kill_all_process(t_data *data)
{
    int i;
    int status;

    i = 0;
    while (i < data->number_of_philosophers)
    {
        kill(data->philo[i], SIGKILL);
        i++;
    }
    usleep(1000);
    i = 0;
    while (i < data->number_of_philosophers)
    {
        waitpid(data->philo[i], &status, WNOHANG);
        if (WIFEXITED(status))
            if (WEXITSTATUS(status) == 1)
                return (i + 1);
        i++;
    }
    return (1);
}

int philo_die(t_data *data)
{
    sem_wait(data->checker);
    if (data->die)
        return (sem_post(data->checker), 1);
    sem_post(data->checker);
    return (0);
}

void    join_threads(pthread_t check_finish, pthread_t check_death, t_data *data)
{
    int i;

    i = 0;
    while (i < data->number_of_philosophers)
    {
        sem_post(data->finish);
        i++;
    }
    sem_post(data->death);
    pthread_join(check_death, NULL);
    pthread_join(check_finish, NULL);
}

void    monitoring(t_data *data)
{
    int         philo_dead;
    pthread_t   check_finish;
    pthread_t   check_death;

    pthread_create(&check_finish, NULL, check_all_finish, data);
    pthread_create(&check_death, NULL, check_one_death, data);
    while (data->must_eat)
    {
        if (!ft_sleep_monitoring(data))
            break ;
        if (philo_die(data))
        {
            philo_dead = kill_all_process(data);
            print_dead(philo_dead, data->start);
            break ;
        }
        if (data->must_eat > 0)
            data->must_eat--;
    }
    join_threads(check_death, check_finish, data);
    pthread_detach(check_death);
    pthread_detach(check_finish);
    wait_philo(data->number_of_philosophers);
}