/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:34:49 by svan-de-          #+#    #+#             */
/*   Updated: 2023/09/09 16:35:01 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	swap_order(pthread_mutex_t **a, pthread_mutex_t **b)
{
	pthread_mutex_t	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	fill_arg(t_philo *arg, t_data *data, int i)
{
	arg[i].number_of_philosophers = data->number_of_philosophers;
	arg[i].name = i + 1;
	arg[i].time_to_die = data->time_to_die;
	arg[i].time_to_eat = data->time_to_eat;
	arg[i].time_to_sleep = data->time_to_sleep;
	arg[i].must_eat = data->must_eat;
	arg[i].printer = &data->printer;
	arg[i].death = &data->death;
	arg[i].syncro = &data->syncro;
	arg[i].all_finish = &data->all_finish;
	arg[i].someone_die = &data->die;
	arg[i].finish = &data->finish;
}

void	init_mutex(pthread_mutex_t *forks, t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_init(&data->death, NULL);
	pthread_mutex_init(&data->syncro, NULL);
	pthread_mutex_init(&data->all_finish, NULL);
	pthread_mutex_init(&data->printer, NULL);
	while (i < data->number_of_philosophers)
		pthread_mutex_init(&forks[i++], NULL);
}

void	init_mutex_and_args(pthread_mutex_t *forks, t_philo *arg, t_data *data)
{
	int	i;

	init_mutex(forks, data);
	i = 0;
	data->die = 0;
	data->finish = 0;
	while (i < data->number_of_philosophers)
	{
		fill_arg(arg, data, i);
		pthread_mutex_init(&(arg[i].meal), NULL);
		if (i != 0)
			(arg[i].forks)[0] = &forks[i - 1];
		else
		{
			if (data->number_of_philosophers > 1)
				(arg[i].forks)[0] = &forks[data->number_of_philosophers - 1];
			else
				(arg[i].forks)[0] = NULL;
		}
		(arg[i].forks)[1] = &forks[i];
		if ((i + 1) % 2 == 0)
			swap_order(&((arg[i].forks)[0]), &((arg[i].forks)[1]));
		i++;
	}
}

void	destroy_mutex(pthread_mutex_t *forks, t_data *data, t_philo *arg)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->death);
	pthread_mutex_destroy(&data->syncro);
	pthread_mutex_destroy(&data->all_finish);
	pthread_mutex_destroy(&data->printer);
	while (i < data->number_of_philosophers)
		pthread_mutex_destroy(&forks[i++]);
	i = 0;
	while (i < data->number_of_philosophers)
		pthread_mutex_destroy(&(arg[i++].meal));
}
