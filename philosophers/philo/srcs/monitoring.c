/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 15:20:00 by svan-de-          #+#    #+#             */
/*   Updated: 2023/09/09 16:45:18 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_all_philo(t_data *data, pthread_t *philos, t_philo *args)
{
	int	i;

	i = -1;
	args[0].start = get_time();
	pthread_mutex_lock(&data->syncro);
	while (++i < data->number_of_philosophers)
	{
		args[i].start = args[0].start;
		args[i].last_meal = args[i].start;
		if (pthread_create(&philos[i], NULL, routine, &args[i]))
		{
			pthread_mutex_lock(&data->death);
			data->die = 1;
			pthread_mutex_unlock(&data->death);
			pthread_mutex_unlock(&data->syncro);
			return (i);
		}
	}
	pthread_mutex_unlock(&data->syncro);
	return (i);
}

int	philo_die(t_philo *arg, int i)
{
	pthread_mutex_lock(&(arg[i].meal));
	if (get_time() - arg[i].last_meal >= arg[i].time_to_die)
	{
		pthread_mutex_unlock(&arg[i].meal);
		return (1);
	}
	pthread_mutex_unlock(&(arg[i].meal));
	return (0);
}

void	join_philos(pthread_t *philos, int number)
{
	int	i;

	i = 0;
	while (i < number)
		pthread_join(philos[i++], NULL);
}

int	monitor_check(t_data *data, t_philo *args)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->all_finish);
	if (data->finish == data->number_of_philosophers)
		return (pthread_mutex_unlock(&data->all_finish), 1);
	pthread_mutex_unlock(&data->all_finish);
	while (i < data->number_of_philosophers)
	{
		if (philo_die(args, i))
		{
			pthread_mutex_lock(&data->death);
			data->die = 1;
			pthread_mutex_unlock(&data->death);
			pthread_mutex_lock(&data->printer);
			print_dead(&args[i]);
			pthread_mutex_unlock(&data->printer);
			return (1);
		}
		i++;
	}
	return (0);
}

int	monitoring(t_data *data, pthread_t *philos, t_philo *args)
{
	int	successful_threads;

	args[0].start = get_time();
	successful_threads = create_all_philo(data, philos, args);
	if (successful_threads != data->number_of_philosophers)
		return (successful_threads);
	while (1)
		if (monitor_check(data, args))
			return (successful_threads);
	return (successful_threads);
}
