/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 15:20:09 by svan-de-          #+#    #+#             */
/*   Updated: 2023/09/09 16:45:40 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_fork(t_philo *philo)
{
	static char	str[100] = {0};
	int			i;

	pthread_mutex_lock(philo->printer);
	if (!access_death(philo))
	{
		i = 0;
		putnbr(get_time() - philo->start, str, &i);
		fill_str(str, "ms ", &i);
		putnbr(philo->name, str, &i);
		fill_str(str, " has taken a fork\n", &i);
		write(1, str, i);
	}
	pthread_mutex_unlock(philo->printer);
}

void	print_eat(t_philo *philo)
{
	static char	str[100] = {0};
	int			i;

	pthread_mutex_lock(philo->printer);
	if (!access_death(philo))
	{
		i = 0;
		putnbr(get_time() - philo->start, str, &i);
		fill_str(str, "ms ", &i);
		putnbr(philo->name, str, &i);
		fill_str(str, " is eating\n", &i);
		write(1, str, i);
	}
	pthread_mutex_unlock(philo->printer);
}

void	print_sleep(t_philo *philo)
{
	static char	str[100] = {0};
	int			i;

	pthread_mutex_lock(philo->printer);
	if (!access_death(philo))
	{
		i = 0;
		putnbr(get_time() - philo->start, str, &i);
		fill_str(str, "ms ", &i);
		putnbr(philo->name, str, &i);
		fill_str(str, " is sleeping\n", &i);
		write(1, str, i);
	}
	pthread_mutex_unlock(philo->printer);
}

void	print_think(t_philo *philo)
{
	static char	str[100] = {0};
	int			i;

	pthread_mutex_lock(philo->printer);
	if (!access_death(philo))
	{
		i = 0;
		putnbr(get_time() - philo->start, str, &i);
		fill_str(str, "ms ", &i);
		putnbr(philo->name, str, &i);
		fill_str(str, " is thinking\n", &i);
		write(1, str, i);
	}
	pthread_mutex_unlock(philo->printer);
}

void	print_dead(t_philo *philo)
{
	static char	str[100] = {0};
	int			i;

	i = 0;
	putnbr(get_time() - philo->start, str, &i);
	fill_str(str, "ms ", &i);
	putnbr(philo->name, str, &i);
	fill_str(str, " died\n", &i);
	write(1, str, i);
}
