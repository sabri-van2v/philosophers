/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:11:03 by svan-de-          #+#    #+#             */
/*   Updated: 2023/09/09 16:11:36 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

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
