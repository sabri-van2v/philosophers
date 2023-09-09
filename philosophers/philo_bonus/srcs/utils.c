/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:08:04 by svan-de-          #+#    #+#             */
/*   Updated: 2023/09/09 16:54:05 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long)((tv.tv_sec * 1000) + (tv.tv_usec / 1000)));
}

void	sleep_philo(t_data *philo, int count)
{
	long	init;

	init = get_time();
	while (get_time() - init < count)
	{
		usleep(1000);
		monitoring_for_process(philo);
	}
}

void	sleep_philo_think(t_data *philo)
{
	while (1)
	{
		usleep(1000);
		monitoring_for_process(philo);
		if (philo->forks->__align > 1)
			break ;
	}
}

void	putnbr(long number, char *str, int *i)
{
	if (number > 9)
	{
		putnbr(number / 10, str, i);
		putnbr(number % 10, str, i);
	}
	else
	{
		str[*i] = number + '0';
		(*i)++;
	}
}

int	ft_atoi(char *str)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}
