/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:08:04 by svan-de-          #+#    #+#             */
/*   Updated: 2023/09/06 14:09:34 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	get_time()
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long)((tv.tv_sec * 1000) + (tv.tv_usec / 1000)));
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

void	fill_str(char *str, char *filler, int *i)
{
	int index_fill;

	index_fill = 0;
	while (filler[index_fill])
	{
		str[*i] = filler[index_fill];
		index_fill++;
		(*i)++;
	}
}

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int ft_atoi(char *str)
{
	int i;
	int result;

	i = 0;
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}