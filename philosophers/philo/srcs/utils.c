#include "philo.h"

long    get_time()
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return ((long)((tv.tv_sec * 1000) + (tv.tv_usec / 1000)));
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

void    putnbr(long number, char *str, int *i)
{
    if (number > 9)
    {
        putnbr(number / 10, str, i);
        putnbr(number % 10, str, i);
    }
    else
    {
        str[*i] = number + '0';
        (*i)++;
    }
}

void    fill_str(char *str, char *filler, int *i)
{
    int index_fill;

    index_fill = 0;
    while (filler[index_fill])
    {
        str[*i] = filler[index_fill];
        index_fill++;
        (*i)++;
    }
}

void    unlock_all(t_philo *philo)
{
    if (philo->forks[0])
        pthread_mutex_unlock(philo->forks[0]);
    pthread_mutex_unlock(philo->forks[1]);
}