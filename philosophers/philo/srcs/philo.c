#include "philo.h"

int main(int argc, char **argv)
{
    t_data  data;

    if (!parsing(argc, argv, &data))
        return (1);
    if (!execute(&data))
        return (1);
}