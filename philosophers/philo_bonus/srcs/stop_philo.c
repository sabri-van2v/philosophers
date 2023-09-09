/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:52:21 by svan-de-          #+#    #+#             */
/*   Updated: 2023/09/09 16:55:18 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	monitoring_for_process(t_data *data)
{
	if (get_time() - data->last_meal >= data->time_to_die)
	{
		sem_post(data->death);
		close_sem(data);
		free(data->philo);
		exit(1);
	}
}

void	wait_philo(int number)
{
	int	i;

	i = 0;
	while (i < number)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
}

void	kill_all_process(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		kill(data->philo[i], SIGKILL);
		i++;
	}
	usleep(1000);
}

int	get_name_of_philo_dying(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		waitpid(data->philo[i], &status, WNOHANG);
		if (WIFEXITED(status))
			if (WEXITSTATUS(status) == 1)
				return (i + 1);
		i++;
	}
	return (1);
}

int	philo_die(t_data *data)
{
	usleep(500);
	sem_wait(data->checker);
	if (data->die)
		return (sem_post(data->checker), 1);
	sem_post(data->checker);
	return (0);
}
