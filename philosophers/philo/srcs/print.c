#include "philo.h"

void    print_fork(int number)
{
    static long start = 0;
    static int  call = 0;
    char        *str;
    int         i;

    if (call == 0)
        return (call++, (void)(start = get_time()));
    str = get_str();
    i = 0;
    putnbr(get_time() - start, str, &i);
    fill_str(str, "ms ", &i);
    putnbr(number, str, &i);
    fill_str(str, " has taken a fork\n", &i);
    write(1, str, i);
}

void    print_eat(int number)
{
    static long start = 0;
    static int  call = 0;
    char        *str;
    int         i;

    if (call == 0)
        return (call++, (void)(start = get_time()));
    str = get_str();
    i = 0;
    putnbr(get_time() - start, str, &i);
    fill_str(str, "ms ", &i);
    putnbr(number, str, &i);
    fill_str(str, " is eating\n", &i);
    write(1, str, i);
}

void    print_sleep(int number)
{
    static long start = 0;
    static int  call = 0;
    char        *str;
    int         i;

    if (call == 0)
        return (call++, (void)(start = get_time()));
    str = get_str();
    i = 0;
    putnbr(get_time() - start, str, &i);
    fill_str(str, "ms ", &i);
    putnbr(number, str, &i);
    fill_str(str, " is sleeping\n", &i);
    write(1, str, i);
}

void    print_think(int number)
{
    static long start = 0;
    static int  call = 0;
    char        *str;
    int         i;

    if (call == 0)
        return (call++, (void)(start = get_time()));
    str = get_str();
    i = 0;
    putnbr(get_time() - start, str, &i);
    fill_str(str, "ms ", &i);
    putnbr(number, str, &i);
    fill_str(str, " is thinking\n", &i);
    write(1, str, i);
}

void    print_dead(int number)
{
    static long start = 0;
    static int  call = 0;
    char        *str;
    int         i;

    if (call == 0)
        return (call++, (void)(start = get_time()));
    str = get_str();
    i = 0;
    putnbr(get_time() - start, str, &i);
    fill_str(str, "ms ", &i);
    putnbr(number, str, &i);
    fill_str(str, " died\n", &i);
    write(1, str, i);
}