#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>

typedef struct s_data
{
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int must_eat;
    int die;
    int finish;
    pthread_mutex_t printer;
    pthread_mutex_t death;
    pthread_mutex_t all_finish;
}   t_data;

typedef struct s_philo
{
    int             number_of_philosophers;
    int             name;
    long            start;
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
    pthread_mutex_t meal;
}   t_philo;

void    print_fork(t_philo *philo);
void    print_eat(t_philo *philo);
void    print_sleep(t_philo *philo);
void    print_think(t_philo *philo);
void    print_dead(t_philo *philo);

int access_death(t_philo *philo);
int    access_all_finish(t_philo *philo);
int    access_printer(t_philo *philo, int type);
void    ft_sleep(int count, t_philo *philo);
char *get_str();

long    get_time();
int ft_strlen(char *str);
int ft_atoi(char *str);
void    putnbr(long number, char *str, int *i);
void    fill_str(char *str, char *filler, int *i);
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

void    call_printers();
void    join_philos(pthread_t *philos, int number);
int    monitoring(t_data *data, pthread_t *philos, t_philo *args);

void    init_mutex_and_args(pthread_mutex_t *forks, t_philo *arg, t_data *data);
void    destroy_mutex(pthread_mutex_t *forks, t_data *data, t_philo *arg);
int    execute(t_data *data);

int main(int argc, char **argv);

#endif