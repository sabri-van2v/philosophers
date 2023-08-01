#include "philo.h"

void    print_philo(t_data *data)
{
    printf("number_of_philosophers : %d\n", data->number_of_philosophers);
    printf("time_to_die : %d\n", data->time_to_die);
    printf("time_to_eat : %d\n", data->time_to_eat);
    printf("time_to_sleep : %d\n", data->time_to_sleep);
    printf("must_eat : %d\n", data->must_eat);
}

int main(int argc, char **argv)
{
    t_data  data;

    if (!parsing(argc, argv, &data))
        return (1);
    //print_philo(&data);
    if (!execute(&data))
        return (1);
}