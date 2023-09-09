/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 15:32:24 by svan-de-          #+#    #+#             */
/*   Updated: 2023/09/09 16:58:33 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <pthread.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <sys/time.h>

typedef struct s_data
{
	int		number_of_philosophers;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		must_eat;
	int		name;
	long	last_meal;
	long	start;
	pid_t	*philo;
	int		all_finish;
	int		die;
	sem_t	*death;
	sem_t	*checker;
	sem_t	*finish;
	sem_t	*forks;
}	t_data;

void	close_sem(t_data *data);
void	destroy_sem(t_data *data);
void	free_mem(t_data *data);
void	destroy_philo(t_data *data, int number);
void	destroy_all(t_data *data);

void	print_fork(int number, long start);
void	print_eat(int number, long start);
void	print_sleep(int number, long start);
void	print_think(int number, long start);
void	print_dead(int number, long start);

long	get_time(void);
void	sleep_philo(t_data *philo, int count);
void	sleep_philo_think(t_data *philo);
int		access_death(t_data *data);
int		access_printer(t_data *data, int type);
int		ft_sleep(int count, t_data *data);
void	putnbr(long number, char *str, int *i);
void	fill_str(char *str, char *filler, int *i);
int		ft_strlen(char *str);
int		ft_atoi(char *str);

void	kill_all_process(t_data *data);
int		get_name_of_philo_dying(t_data *data);

void	take_forks(t_data *data);
void	is_eating(t_data *data);
void	is_sleeping(t_data *data);
void	is_thinking(t_data *data);
void	monitoring_for_process(t_data *data);
void	routine(t_data *data);

void	wait_philo(int number);
int		philo_die(t_data *data);
void	monitoring(t_data *data);

void	init_semaphore(t_data *data);
void	create_philos(t_data *data);
void	execute(t_data *data);

void	error_argument(void);
void	fill_data(t_data *data, char **argv);
int		is_valid_number(char *str);
int		check_args(int argc, char **argv);
void	parsing(int argc, char **argv, t_data *data);

int		main(int argc, char **argv);

#endif