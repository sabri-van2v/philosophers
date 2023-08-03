#include "philo.h"

int access_death(t_philo *philo)
{
    pthread_mutex_lock(philo->death);
    if (*philo->someone_die)
        return (pthread_mutex_unlock(philo->death), 1);
    pthread_mutex_unlock(philo->death);
    return (0);
}

void    access_all_finish(t_philo *philo)
{
    pthread_mutex_lock(philo->all_finish);
    (*philo->finish)++;
    pthread_mutex_unlock(philo->all_finish);
}

int    access_printer(t_philo *philo, int type)
{
    pthread_mutex_lock(philo->printer);
    if (!access_death(philo))
    {
        if (type == FORK)
            print_fork(philo->name);
        else if (type == EAT)
            print_eat(philo->name);
        else if (type == SLEEP)
            print_sleep(philo->name);
        else if (type == THINK)
            print_think(philo->name);
        return (pthread_mutex_unlock(philo->printer), 1);
    }
    pthread_mutex_unlock(philo->printer);
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
        if (access_death(philo))
            return ;
    }
}

char *get_str()
{
    static char *str = NULL;
    static int  call = 0;

    if (call == 0)
    {
        call++;
        str = malloc(100);
        if (!str)
            return (NULL);
        str = memset(str, 0, 100);
        return (str);
    }
    return (str);
}