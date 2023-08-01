#include "philo.h"

void    print_fork(int number)
{
    static long start = 0;
    static int  call = 0;

    if (call == 0)
        return (call++, (void)(start = get_time()));
    putnbr(get_time() - start);
    write(1, "ms ", 3);
    putnbr(number);
    write(1, " has taken a fork\n", 18);
}

void    print_eat(int number)
{
    static long start = 0;
    static int  call = 0;

    if (call == 0)
        return (call++, (void)(start = get_time()));
    putnbr(get_time() - start);
    write(1, "ms ", 3);
    putnbr(number);
    write(1, " is eating\n", 11);
}

void    print_sleep(int number)
{
    static long start = 0;
    static int  call = 0;

    if (call == 0)
        return (call++, (void)(start = get_time()));
    putnbr(get_time() - start);
    write(1, "ms ", 3);
    putnbr(number);
    write(1, " is sleeping\n", 13);
}

void    print_think(int number)
{
    static long start = 0;
    static int  call = 0;

    if (call == 0)
        return (call++, (void)(start = get_time()));
    putnbr(get_time() - start);
    write(1, "ms ", 3);
    putnbr(number);
    write(1, " is thinking\n", 13);
}

void    print_dead(int number)
{
    static long start = 0;
    static int  call = 0;

    if (call == 0)
        return (call++, (void)(start = get_time()));
    putnbr(get_time() - start);
    write(1, "ms ", 3);
    putnbr(number);
    write(1, " died\n", 6);
}