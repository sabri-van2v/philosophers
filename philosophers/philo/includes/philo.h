#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct s_data
{
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int must_eat;
}   t_data;

int ft_strlen(char *str);
int ft_atoi(char *str);

void    error_argument();
void    fill_data(t_data *data, char **argv);
int is_valid_number(char *str);
int check_args(int argc, char **argv);
int parsing(int argc, char **argv, t_data *data);

void    print_philo(t_data *data);
int main(int argc, char **argv);

#endif