#include "philo.h"

long    get_time()
{
    struct timeval tv;
    long            time;

    if (gettimeofday(&tv, NULL) == -1)
        return (write(2, "gettimeofday failed\n", 20), -1);
    time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    return (time);
}

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

int ft_atoi(char *str)
{
    int i;
    int result;

    i = 0;
    result = 0;
    while (str[i] >= '0' && str[i] <= '9')
    {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return (result);
}

void    putnbr(long number)
{
    if (number > 9)
    {
        putnbr(number / 10);
        putnbr(number % 10);
    }
    else
        write(1, &"0123456789"[number], 1);
}

void    unlock_all(t_philo *philo)
{
    if (philo->forks[0])
        pthread_mutex_unlock(philo->forks[0]);
    pthread_mutex_unlock(philo->forks[1]);
}