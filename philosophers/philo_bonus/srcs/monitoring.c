/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 15:46:42 by svan-de-          #+#    #+#             */
/*   Updated: 2023/09/09 17:02:47 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_all_finish(void *arg)
{
	t_data			*data;
	int				i;

	data = (t_data *)arg;
	i = 0;
	while (1)
	{
		if (i == data->number_of_philosophers)
			break ;
		sem_wait(data->finish);
		i++;
	}
	sem_wait(data->checker);
	data->all_finish = 1;
	sem_post(data->checker);
	return (NULL);
}

void	*check_one_death(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	sem_wait(data->death);
	sem_wait(data->checker);
	data->die = 1;
	sem_post(data->checker);
	return (NULL);
}

void	join_threads(pthread_t check_finish, pthread_t check_death,
t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		sem_post(data->finish);
		i++;
	}
	sem_post(data->death);
	pthread_join(check_death, NULL);
	pthread_join(check_finish, NULL);
}

int	monitor_check(t_data *data)
{
	int	philo_dead;

	sem_wait(data->checker);
	if (data->all_finish)
	{
		sem_post(data->checker);
		kill_all_process(data);
		return (1);
	}
	sem_post(data->checker);
	if (philo_die(data))
	{
		kill_all_process(data);
		philo_dead = get_name_of_philo_dying(data);
		print_dead(philo_dead, data->start);
		return (1);
	}
	return (0);
}

void	monitoring(t_data *data)
{
	pthread_t	check_finish;
	pthread_t	check_death;

	if (pthread_create(&check_death, NULL, check_one_death, data) == -1)
		return ;
	if (pthread_create(&check_finish, NULL, check_all_finish, data) == -1)
	{
		sem_post(data->death);
		pthread_join(check_death, NULL);
		return ;
	}
	while (1)
		if (monitor_check(data))
			break ;
	join_threads(check_death, check_finish, data);
	wait_philo(data->number_of_philosophers);
}
