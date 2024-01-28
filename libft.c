/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 11:57:28 by asemsey           #+#    #+#             */
/*   Updated: 2024/01/28 13:37:30 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*free_all(void **x)
{
	int	i;

	i = 0;
	while (x && x[i])
	{
		free(x[i]);
		x[i] = NULL;
		i++;
	}
	free(x);
	x = NULL;
	return (NULL);
}

int	ft_atoi(const char *str)
{
	int	negative;
	int	res;

	negative = 1;
	res = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			negative *= -1;
		str++;
	}
	while ('0' <= *str && *str <= '9')
	{
		res = res * 10 + *str - '0';
		str++;
	}
	return (negative * res);
}
