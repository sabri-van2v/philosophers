#include "philo.h"

void    take_forks(t_philo *philo)
{
    pthread_mutex_lock(philo->forks[0]);
    pthread_mutex_lock(philo->printer);
    if (!*(philo->someone_die))
        print_fork(philo->name);
    pthread_mutex_unlock(philo->printer);
    pthread_mutex_lock(philo->forks[1]);
    pthread_mutex_lock(philo->printer);
    if (!*(philo->someone_die))
        print_fork(philo->name);
    pthread_mutex_unlock(philo->printer);
}

void    is_eating(t_philo *philo)
{
    pthread_mutex_lock(philo->printer);
    if (!*(philo->someone_die))
        print_eat(philo->name);
    else
        return ;
    pthread_mutex_unlock(philo->printer);
    philo->last_meal = get_time();
    usleep(philo->time_to_eat * 1000);
}

void    is_sleeping(t_philo *philo)
{
    pthread_mutex_unlock(philo->forks[0]);
    pthread_mutex_unlock(philo->forks[1]);
    pthread_mutex_lock(philo->printer);
    if (!*(philo->someone_die))
        print_sleep(philo->name);
    else
        return ;
    pthread_mutex_unlock(philo->printer);
    usleep(philo->time_to_sleep * 1000);
}

void    is_thinking(t_philo *philo)
{
    pthread_mutex_lock(philo->printer);
    if (!*(philo->someone_die))
        print_think(philo->name);
    pthread_mutex_unlock(philo->printer);
}

void    *routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if (philo->name % 2 == 0)
        usleep(philo->time_to_eat * 1000);
    while (philo->must_eat)
    {
        if (*(philo->someone_die))
            return (unlock_all(philo), NULL);
        take_forks(philo);
        if (*(philo->someone_die))
            return (unlock_all(philo), NULL);
        is_eating(philo);
        if (*(philo->someone_die))
            return (unlock_all(philo), NULL);
        is_sleeping(philo);
        if (*(philo->someone_die))
            return (unlock_all(philo), NULL);
        is_thinking(philo);
        if (philo->must_eat > 0)
            philo->must_eat--;
    }
    return (NULL);
}