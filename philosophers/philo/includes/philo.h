#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_data
{
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int must_eat;
    int die;
    long    start;
    int finish;
    pthread_mutex_t printer;
    pthread_mutex_t death;
    pthread_mutex_t all_finish;
}   t_data;

typedef struct s_philo
{
    int             name;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             must_eat;
    long            last_meal;
    int             *someone_die;
    int             *finish;
    pthread_mutex_t *forks[2];
    pthread_mutex_t *printer;
    pthread_mutex_t *death;
    pthread_mutex_t *all_finish;
}   t_philo;

void    print_fork(int number);
void    print_eat(int number);
void    print_sleep(int number);
void    print_think(int number);
void    print_dead(int number);

long    get_time();
int ft_strlen(char *str);
int ft_atoi(char *str);
void    putnbr(long number);
void    unlock_all(t_philo *philo);

void    error_argument();
void    fill_data(t_data *data, char **argv);
int is_valid_number(char *str);
int check_args(int argc, char **argv);
int parsing(int argc, char **argv, t_data *data);

void    take_forks(t_philo *philo);
void    is_eating(t_philo *philo);
void    is_sleeping(t_philo *philo);
void    is_thinking(t_philo *philo);
void    *routine(void *arg);

void    init_last_meals(long start, int number, t_philo *args);
void    call_printers();
void    join_philos(pthread_t *philos, int number);
void    monitoring(t_data *data, pthread_t *philos, t_philo *args);

void    init_mutex_and_args(pthread_mutex_t *forks, t_philo *arg, t_data *data);
void    destroy_mutex(pthread_mutex_t *forks, t_data *data);
int    execute(t_data *data);

int main(int argc, char **argv);

#endif