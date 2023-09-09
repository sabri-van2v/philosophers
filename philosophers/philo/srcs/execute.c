/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 15:19:55 by svan-de-          #+#    #+#             */
/*   Updated: 2023/09/09 16:35:22 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	execute(t_data *data)
{
	pthread_t		*philos;
	pthread_mutex_t	*forks;
	t_philo			*arg;
	int				successful_threads;

	philos = malloc(sizeof(pthread_t) * data->number_of_philosophers);
	forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
	arg = malloc(sizeof(t_philo) * data->number_of_philosophers);
	if (!philos || !forks || !arg)
		return (free(philos), free(forks), free(arg), 0);
	init_mutex_and_args(forks, arg, data);
	successful_threads = monitoring(data, philos, arg);
	join_philos(philos, successful_threads);
	destroy_mutex(forks, data, arg);
	(free(philos), free(forks), free(arg));
	return (1);
}
