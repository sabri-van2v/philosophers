#include "philo_bonus.h"

long    get_time()
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return ((long)((tv.tv_sec * 1000) + (tv.tv_usec / 1000)));
}

// void    access_printer(t_data *data, int type)
// {
//     sem_wait(data->printer);
//     if (type == FORK)
//         print_fork(data->name, data->start);
//     else if (type == EAT)
//         print_eat(data->name, data->start);
//     else if (type == SLEEP)
//         print_sleep(data->name, data->start);
//     else if (type == THINK)
//         print_think(data->name, data->start);
//     sem_post(data->printer);
// }

int ft_sleep(int count, t_data *data)
{
    long    current;

    current = get_time();
    if (current - data->last_meal + count >= data->time_to_die)
    {
        count = data->time_to_die - (current - data->last_meal);
        current = -1;
    }
    usleep(count * 1000);
    if (current == -1)
        return (0);
    return (1);
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