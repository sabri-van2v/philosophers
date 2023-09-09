/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 15:19:58 by svan-de-          #+#    #+#             */
/*   Updated: 2023/09/09 16:18:33 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	access_death(t_philo *philo)
{
	pthread_mutex_lock(philo->death);
	if (*philo->someone_die)
		return (pthread_mutex_unlock(philo->death), 1);
	pthread_mutex_unlock(philo->death);
	return (0);
}

int	access_all_finish(t_philo *philo)
{
	pthread_mutex_lock(philo->all_finish);
	if (*philo->finish == philo->number_of_philosophers)
	{
		pthread_mutex_unlock(philo->all_finish);
		return (1);
	}
	pthread_mutex_unlock(philo->all_finish);
	return (0);
}

void	ft_sleep(int count, t_philo *philo)
{
	long	init;

	while (count > 0)
	{
		init = get_time();
		if (count > 1000)
		{
			usleep(1000000);
			count -= get_time() - init;
		}
		else
		{
			usleep(count * 1000);
			count = 0;
		}
		if (access_death(philo) || access_all_finish(philo))
			return ;
	}
}
