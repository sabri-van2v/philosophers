/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:49:42 by svan-de-          #+#    #+#             */
/*   Updated: 2023/09/09 17:25:44 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

sem_t	*create_sem(sem_t **sem, char *name, int number)
{
	return ((*sem = sem_open(name, O_CREAT, 0644, number)));
}

void	init_semaphore(t_data *data)
{
	if (create_sem(&data->forks, "forks", data->number_of_philosophers)
		== SEM_FAILED
		|| create_sem(&data->finish, "finish", 0) == SEM_FAILED
		|| create_sem(&data->checker, "checker", 1) == SEM_FAILED
		|| create_sem(&data->death, "death", 0) == SEM_FAILED)
		(destroy_sem(data), exit(1));
}

void	create_philos(t_data *data)
{
	int	i;

	i = 0;
	data->start = get_time();
	data->last_meal = data->start;
	while (i < data->number_of_philosophers)
	{
		data->philo[i] = fork();
		if (data->philo[i] == -1)
			write(2, "fork failed\n", 12);
		if (data->philo[i] == 0)
		{
			data->name = i + 1;
			if (data->name % 2 == 0)
				usleep(data->time_to_eat * 1000);
			routine(data);
		}
		i++;
	}
}

void	execute(t_data *data)
{
	data->philo = malloc(sizeof(pid_t) * data->number_of_philosophers);
	if (!data->philo)
		exit(1);
	init_semaphore(data);
	create_philos(data);
	monitoring(data);
	destroy_sem(data);
}
