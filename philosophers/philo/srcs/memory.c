#include "philo.h"

int access_death(t_philo *philo)
{
    pthread_mutex_lock(philo->death);
    if (*philo->someone_die)
        return (pthread_mutex_unlock(philo->death), 1);
    pthread_mutex_unlock(philo->death);
    return (0);
}

int    access_all_finish(t_philo *philo)
{
    pthread_mutex_lock(philo->all_finish);
    if (*philo->finish == philo->number_of_philosophers)
    {
        pthread_mutex_unlock(philo->all_finish);
        return (1);
    }
    pthread_mutex_unlock(philo->all_finish);
    return (0);
}

void    ft_sleep(int count, t_philo *philo)
{
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
        if (access_death(philo) || access_all_finish(philo))
            return ;
    }
}
