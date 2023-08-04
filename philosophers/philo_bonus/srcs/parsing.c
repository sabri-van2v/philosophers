#include "philo_bonus.h"

void    error_argument()
{
    write(2, "Error\nInvalid arguments\n", 24);
}

void    fill_data(t_data *data, char **argv)
{
    data->number_of_philosophers = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    if (argv[5])
        data->must_eat = ft_atoi(argv[5]);
    else
        data->must_eat = -1;
}

int is_valid_number(char *str)
{
    int i;
    int result;

    i = 0;
    result = 0;
    while (str[i] >= '0' && str[i] <= '9')
    {
        result = result * 10 + (str[i] - '0');
        if (result < 0)
            return (0);
        i++;
    }
    if (i != ft_strlen(str) || str[0] == '0' || i == 0)
        return (0);
    return (1);
}

int check_args(int argc, char **argv)
{
    int i;

    i = 1;
    if (argc != 5 && argc != 6)
        return (0);
    while (argv[i])
    {
        if (!is_valid_number(argv[i]))
            return (0);
        i++;
    }
    return (1);
}

void    parsing(int argc, char **argv, t_data *data)
{
    if (!check_args(argc, argv))
        return (error_argument(), exit(1));
    fill_data(data, argv);
}