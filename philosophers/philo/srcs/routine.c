#include "philo.h"

void    take_forks(t_philo *philo)
{
    usleep(1000);
    if (philo->forks[0])
    {
        pthread_mutex_lock(philo->forks[0]);
        if (!access_printer(philo, FORK))
            return ;
    }
    pthread_mutex_lock(philo->forks[1]);
    if (!access_printer(philo, FORK))
        return ;
}

void    is_eating(t_philo *philo)
{
    pthread_mutex_lock(&philo->meal);
    philo->last_meal = get_time();
    pthread_mutex_unlock(&philo->meal);
    if (!access_printer(philo, EAT))
        return ;
    ft_sleep(philo->time_to_eat, philo);
}

void    is_sleeping(t_philo *philo)
{
    pthread_mutex_unlock(philo->forks[0]);
    pthread_mutex_unlock(philo->forks[1]);
    if (!access_printer(philo, SLEEP))
        return ;
    ft_sleep(philo->time_to_sleep, philo);
}

void    is_thinking(t_philo *philo)
{
    access_printer(philo, THINK);
}

void    *routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if (!philo->forks[0])
        return (take_forks(philo), unlock_all(philo), NULL);
    if (philo->name % 2 == 0)
        ft_sleep(philo->time_to_eat, philo);
    while (philo->must_eat)
    {
        if (access_death(philo))
            return (NULL);
        take_forks(philo);
        is_eating(philo);
        is_sleeping(philo);
        is_thinking(philo);
        pthread_mutex_lock(&philo->meal);
        if (philo->must_eat > 0)
            philo->must_eat--;
        pthread_mutex_unlock(&philo->meal);
    }
    pthread_mutex_lock(philo->all_finish);
    (*philo->finish)++;
    pthread_mutex_unlock(philo->all_finish);
    return (NULL);
}
