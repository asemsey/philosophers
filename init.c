/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 15:29:02 by asemsey           #+#    #+#             */
/*   Updated: 2024/01/29 15:29:51 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// 0-fail   1-endless   2-limit
// maybe check reasonable input values?
int	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5)
		return (0);
	while (i < 5)
	{
		if (ft_atoi(argv[i]) == 0)
			return (0);
		i++;
	}
	if (argc == 6)
	{
		if (ft_atoi(argv[5]) == 0)
			return (0);
		return (2);
	}
	return (1);
}

t_data	*get_data(int argc, char **argv)
{
	t_data	*data;
	int		i;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->life_time = ft_atoi(argv[2]);
	data->eat_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
		data->min_meals = ft_atoi(argv[5]);
	i = 0;
	return (data);
}