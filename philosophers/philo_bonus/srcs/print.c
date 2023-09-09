/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 15:46:49 by svan-de-          #+#    #+#             */
/*   Updated: 2023/09/09 15:46:49 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_fork(int number, long start)
{
	static char	str[100] = {0};
	int			i;

	i = 0;
	putnbr(get_time() - start, str, &i);
	fill_str(str, "ms ", &i);
	putnbr(number, str, &i);
	fill_str(str, " has taken a fork\n", &i);
	write(1, str, i);
}

void	print_eat(int number, long start)
{
	static char	str[100] = {0};
	int			i;

	i = 0;
	putnbr(get_time() - start, str, &i);
	fill_str(str, "ms ", &i);
	putnbr(number, str, &i);
	fill_str(str, " is eating\n", &i);
	write(1, str, i);
}

void	print_sleep(int number, long start)
{
	static char	str[100] = {0};
	int			i;

	i = 0;
	putnbr(get_time() - start, str, &i);
	fill_str(str, "ms ", &i);
	putnbr(number, str, &i);
	fill_str(str, " is sleeping\n", &i);
	write(1, str, i);
}

void	print_think(int number, long start)
{
	static char	str[100] = {0};
	int			i;

	i = 0;
	putnbr(get_time() - start, str, &i);
	fill_str(str, "ms ", &i);
	putnbr(number, str, &i);
	fill_str(str, " is thinking\n", &i);
	write(1, str, i);
}

void	print_dead(int number, long start)
{
	static char	str[100] = {0};
	int			i;

	i = 0;
	putnbr(get_time() - start, str, &i);
	fill_str(str, "ms ", &i);
	putnbr(number, str, &i);
	fill_str(str, " died\n", &i);
	write(1, str, i);
}
