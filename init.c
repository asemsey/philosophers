/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 15:29:02 by asemsey           #+#    #+#             */
/*   Updated: 2024/01/28 15:31:21 by asemsey          ###   ########.fr       */
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

// array of philosopers with neighbours, life and state. no thread yet!
t_philo	**get_phil(int life, int count)
{
	int		i;
	t_philo	**phil;

	i = 0;
	phil = (t_philo	**)malloc(sizeof(t_philo *) * (count + 1));
	if (!phil)
		return (NULL);
	while (i < count)
	{
		phil[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!phil[i])
			ft_error(NULL, phil);
		phil[i]->left = i;
		if (i == 0)
			phil[i]->left = count;
		phil[i]->name = i + 1;
		phil[i]->right = i + 2;
		if (i + 2 > count)
			phil[i]->right = 1;
		phil[i]->life = life;
		phil[i]->state = 0;
		i++;
	}
	phil[i] = NULL;
	return (phil);
}

void	get_data(int argc, char **argv, t_philo **phil)
{
	t_data	*data;
	int		i;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return ;
	data->life_time = ft_atoi(argv[2]);
	data->eat_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
		data->min_meals = ft_atoi(argv[5]);
	i = 0;
	while (phil[i])
		phil[i++]->data = data;
}

void	print_philo(t_philo **phil)
{
	int	i;

	i = 0;
	if (!phil)
		return ;
	printf("left  name  right || state  life\n");
	printf("--------------------------------\n");
	while (phil[i])
	{
		printf("%d     %d     %d     || %d      %d\n", phil[i]->left,\
			phil[i]->name, phil[i]->right, phil[i]->state, phil[i]->data->life_time);
		i++;
	}
	printf("--------------------------------\n");
}
