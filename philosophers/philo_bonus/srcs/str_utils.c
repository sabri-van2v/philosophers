/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:54:19 by svan-de-          #+#    #+#             */
/*   Updated: 2023/09/09 16:54:32 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	fill_str(char *str, char *filler, int *i)
{
	int	index_fill;

	index_fill = 0;
	while (filler[index_fill])
	{
		str[*i] = filler[index_fill];
		index_fill++;
		(*i)++;
	}
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
